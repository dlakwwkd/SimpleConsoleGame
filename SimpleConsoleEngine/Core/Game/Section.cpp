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
        , objectList{}
    {
        boundary.left = _pos.x - _radius;
        boundary.top = _pos.y - _radius;
        boundary.right = _pos.x + _radius;
        boundary.bottom = _pos.y + _radius;
    }

    bool                    IsOutOfBoundary(const ObjectPtr& _obj, OUT Direction& _dir);
    bool                    RegisterCollision(const ObjectPtr& _obj, Direction _dir);
    SectionPtr              BuildSection(Direction _dir) const;

    POINT                   centerPos;
    LONG                    radius;
    RECT					boundary;
    NearbySections			nearSections;
    std::list<ObjectRef>	objectList;
};


Section::Section(const POINT& _pos, const LONG& _radius) noexcept
    : pimpl{ std::make_unique<impl>(_pos, _radius) }
{
}

Section::~Section()
{
}


void Section::SyncCollision(const ObjectPtr& _obj)
{
    if (_obj == nullptr)
        return;

    Direction dir;
    if (pimpl->IsOutOfBoundary(_obj, dir))
    {
        UnRegisterCollision(_obj);
        pimpl->RegisterCollision(_obj, dir);
    }
}

void Section::CollisionCheck()
{
    if (pimpl->objectList.size() < 2)
        return;

    const float UNIT_RADIUS = 0.5f;
    auto iterEnd = pimpl->objectList.end();
    --iterEnd;
    for (auto iter = pimpl->objectList.begin(); iter != iterEnd;)
    {
        if (auto objectA = (*iter).lock())
        {
            auto iter2 = iter;
            ++iter2;
            for (; iter2 != pimpl->objectList.end(); ++iter2)
            {
                if (auto objectB = (*iter2).lock())
                {
                    auto collisionA = std::dynamic_pointer_cast<CollisionComponent>(objectA->GetCollision());
                    auto collisionB = std::dynamic_pointer_cast<CollisionComponent>(objectB->GetCollision());
                    if (CollisionComponent::IsCollisionAble(collisionA, collisionB))
                    {
                        const Vec2 posA = objectA->GetPos();
                        const Vec2 posB = objectB->GetPos();
                        if (posA.GetX() + UNIT_RADIUS > posB.GetX() - UNIT_RADIUS &&
                            posA.GetX() - UNIT_RADIUS < posB.GetX() + UNIT_RADIUS &&
                            posA.GetY() - UNIT_RADIUS < posB.GetY() + UNIT_RADIUS &&
                            posA.GetY() + UNIT_RADIUS > posB.GetY() - UNIT_RADIUS)
                        {
                            if (collisionA->CanAttack(collisionB))
                            {
                                collisionB->Hitted(collisionA->GetDamage());
                            }
                            if (collisionB->CanAttack(collisionA))
                            {
                                collisionA->Hitted(collisionB->GetDamage());
                            }
                        }
                    }
                }
            }
            ++iter;
            continue;
        }
        // 유닛이 존재하지 않으면 리스트에서 지운다.
        iter = pimpl->objectList.erase(iter);
    }
}


bool Section::RegisterCollision(const ObjectPtr& _obj)
{
    if (_obj == nullptr)
        return false;

    auto collision = std::dynamic_pointer_cast<CollisionComponent>(_obj->GetCollision());
    if (collision == nullptr)
        return false;

    Direction dir;
    if (pimpl->IsOutOfBoundary(_obj, dir))
    {
        // 유닛이 바운더리 바깥이면 해당 방향의 섹션에 등록을 시도한다.
        return pimpl->RegisterCollision(_obj, dir);
    }
    // 유닛 리스트에 등록하고, 유닛에게 등록된 섹션을 알려준다.
    pimpl->objectList.push_back(_obj);
    collision->SetSection(shared_from_this());
    return true;
}

void Section::UnRegisterCollision(const ObjectPtr& _obj)
{
    auto collision = std::dynamic_pointer_cast<CollisionComponent>(_obj->GetCollision());
    if (collision != nullptr)
    {
        collision->SetSection(nullptr);
    }
    pimpl->objectList.remove_if([&_obj](auto& target)
    {
        return target.lock() == _obj;
    });
}

void Section::ClearCollisionList()
{
    pimpl->objectList.clear();
}


bool Section::impl::IsOutOfBoundary(const ObjectPtr& _obj, OUT Direction& _dir)
{
    auto x = _obj->GetPos().GetX();
    auto y = _obj->GetPos().GetY();
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

bool Section::impl::RegisterCollision(const ObjectPtr& _obj, Direction _dir)
{
    // 해당 방향에 섹션이 존재하면, 바로 등록을 시도한다.
    if (auto section = nearSections[_dir].lock())
    {
        return section->RegisterCollision(_obj);
    }
    // 섹션이 존재하지 않으면, 새롭게 생성하고, 등록을 시도한다.
    auto newSection = BuildSection(_dir);
    if (newSection == nullptr)
        return false;

    return newSection->RegisterCollision(_obj);
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
