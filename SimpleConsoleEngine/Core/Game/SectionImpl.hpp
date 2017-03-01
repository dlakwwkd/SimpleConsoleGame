#include "GameManager.h"
#include "Composite/Unit/Unit.h"
#include "../Math/Vec2.h"
SCE_START

/////////////////////////////////////////////////////////////////////////////////////////
struct Section::impl
{
    impl(const POINT& _pos, const LONG& _radius) noexcept
        : centerPos{ _pos }
        , radius{ _radius }
        , nearSections{}
        , unitList{}
    {
        boundary.left = _pos.x - _radius;
        boundary.top = _pos.y - _radius;
        boundary.right = _pos.x + _radius;
        boundary.bottom = _pos.y + _radius;
    }

    bool                IsOutOfBoundary(const UnitPtr& _unit, OUT Direction& _dir);
    bool                RegisterCollision(const UnitPtr& _unit, Direction _dir);
    SectionPtr          BuildSection(Direction _dir) const;

    POINT               centerPos;
    LONG                radius;
    RECT                boundary;
    NearbySections      nearSections;
    std::list<UnitRef>  unitList;
};

/////////////////////////////////////////////////////////////////////////////////////////
bool Section::impl::IsOutOfBoundary(const UnitPtr& _unit, OUT Direction& _dir)
{
    auto x = _unit->GetPos().GetX();
    auto y = _unit->GetPos().GetY();
    if (x < boundary.left)
    {
        _dir = Direction::LEFT;
        return true;
    }
    if (y < boundary.top)
    {
        _dir = Direction::TOP;
        return true;
    }
    if (x > boundary.right)
    {
        _dir = Direction::RIGHT;
        return true;
    }
    if (y > boundary.bottom)
    {
        _dir = Direction::BOTTOM;
        return true;
    }
    return false;
}

/////////////////////////////////////////////////////////////////////////////////////////
bool Section::impl::RegisterCollision(const UnitPtr& _unit, Direction _dir)
{
    // 해당 방향에 섹션이 존재하면, 바로 등록을 시도한다.
    if (auto section = nearSections[_dir].lock())
    {
        return section->RegisterCollision(_unit);
    }
    // 섹션이 존재하지 않으면, 새롭게 생성하고, 등록을 시도한다.
    auto newSection = BuildSection(_dir);
    if (newSection == nullptr)
        return false;

    return newSection->RegisterCollision(_unit);
}

/////////////////////////////////////////////////////////////////////////////////////////
Section::SectionPtr Section::impl::BuildSection(Direction _dir) const
{
    // 1. 생성할 위치 계산
    auto createPos = centerPos;
    auto diameter = radius * 2;
    switch (_dir)
    {
    case Direction::LEFT:    createPos.x -= diameter; break;
    case Direction::TOP:     createPos.y -= diameter; break;
    case Direction::RIGHT:   createPos.x += diameter; break;
    case Direction::BOTTOM:  createPos.y += diameter; break;
    default:
        return nullptr;
    }

    // 2. 생성하려는 위치에 이미 섹션이 있으면 해당 섹션 리턴
    static auto& gm = SCE::GameManager::GetInstance();
    auto exist = gm.FindSection(createPos);
    if (exist != nullptr)
        return exist;

    // 3. 새로 섹션을 생성한 후 게임에 등록 (유일한 shared count)
    auto newSection = ObjectPool<Section>::Get(createPos, radius);
    gm.RegisterBuiltSection(newSection, createPos);

    // 4. 주변 섹션들과 연결
    if (auto left = gm.FindSection({ createPos.x - diameter, createPos.y }))
    {
        newSection->pimpl->nearSections[Direction::LEFT] = left;
        left->pimpl->nearSections[Direction::RIGHT] = newSection;
    }
    if (auto top = gm.FindSection({ createPos.x, createPos.y - diameter }))
    {
        newSection->pimpl->nearSections[Direction::TOP] = top;
        top->pimpl->nearSections[Direction::BOTTOM] = newSection;
    }
    if (auto right = gm.FindSection({ createPos.x + diameter, createPos.y }))
    {
        newSection->pimpl->nearSections[Direction::RIGHT] = right;
        right->pimpl->nearSections[Direction::LEFT] = newSection;
    }
    if (auto bottom = gm.FindSection({ createPos.x, createPos.y + diameter }))
    {
        newSection->pimpl->nearSections[Direction::BOTTOM] = bottom;
        bottom->pimpl->nearSections[Direction::TOP] = newSection;
    }
    return newSection;
}

SCE_END
