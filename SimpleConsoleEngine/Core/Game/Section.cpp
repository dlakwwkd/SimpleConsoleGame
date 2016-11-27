#include "stdafx.h"
#include "Section.h"
#include "GameManager.h"
#include "Composite/Unit/Unit.h"
#include "Component/CollisionComponent/CollisionComponent.h"
#include "../Math/Vec2.h"
SCE_START


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
    RECT				boundary;
    NearbySections		nearSections;
    std::list<UnitRef>	unitList;
};


Section::Section(const POINT& _pos, const LONG& _radius) noexcept
    : pimpl{ std::make_unique<impl>(_pos, _radius) }
{
}

Section::~Section()
{
}


void Section::SyncCollision(const UnitPtr& _unit)
{
    if (_unit == nullptr)
        return;

    Direction dir;
    if (pimpl->IsOutOfBoundary(_unit, dir))
    {
        UnRegisterCollision(_unit);
        pimpl->RegisterCollision(_unit, dir);
    }
}

void Section::CollisionCheck()
{
    if (pimpl->unitList.size() < 2)
        return;

    const float UNIT_RADIUS = 0.5f;
    auto iterEnd = pimpl->unitList.end();
    --iterEnd;
    for (auto iter = pimpl->unitList.begin(); iter != iterEnd;)
    {
        if (auto unitA = (*iter).lock())
        {
            auto iter2 = iter;
            ++iter2;
            for (; iter2 != pimpl->unitList.end(); ++iter2)
            {
                if (auto unitB = (*iter2).lock())
                {
                    auto collisionA = unitA->ICollisionObject::Get<CollisionComponent>();
                    auto collisionB = unitB->ICollisionObject::Get<CollisionComponent>();
                    if (CollisionComponent::IsCollisionAble(collisionA, collisionB))
                    {
                        const Vec2 posA = unitA->GetPos();
                        const Vec2 posB = unitB->GetPos();
                        if (posA.GetX() + UNIT_RADIUS > posB.GetX() - UNIT_RADIUS &&
                            posA.GetX() - UNIT_RADIUS < posB.GetX() + UNIT_RADIUS &&
                            posA.GetY() - UNIT_RADIUS < posB.GetY() + UNIT_RADIUS &&
                            posA.GetY() + UNIT_RADIUS > posB.GetY() - UNIT_RADIUS)
                        {
                            if (collisionA->CanAttack(collisionB))
                            {
                                unitB->Hitted(collisionA->GetDamage());
                            }
                            if (collisionB->CanAttack(collisionA))
                            {
                                unitA->Hitted(collisionB->GetDamage());
                            }
                        }
                    }
                }
            }
            ++iter;
            continue;
        }
        // 유닛이 존재하지 않으면 리스트에서 지운다.
        iter = pimpl->unitList.erase(iter);
    }
}


bool Section::RegisterCollision(const UnitPtr& _unit)
{
    if (_unit == nullptr)
        return false;

    auto collision = _unit->ICollisionObject::Get<CollisionComponent>();
    if (collision == nullptr)
        return false;

    Direction dir;
    if (pimpl->IsOutOfBoundary(_unit, dir))
    {
        // 유닛이 바운더리 바깥이면 해당 방향의 섹션에 등록을 시도한다.
        return pimpl->RegisterCollision(_unit, dir);
    }
    // 유닛 리스트에 등록하고, 유닛에게 등록된 섹션을 알려준다.
    pimpl->unitList.push_back(_unit);
    collision->SetSection(shared_from_this());
    return true;
}

void Section::UnRegisterCollision(const UnitPtr& _unit)
{
    auto collision = _unit->ICollisionObject::Get<CollisionComponent>();
    if (collision != nullptr)
    {
        collision->SetSection(nullptr);
    }
    pimpl->unitList.remove_if([&_unit](auto& target)
    {
        return target.lock() == _unit;
    });
}

void Section::ClearCollisionList()
{
    pimpl->unitList.clear();
}


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
