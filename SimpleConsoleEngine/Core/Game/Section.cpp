#include "stdafx.h"
#include "Section.h"
#include "SectionImpl.hpp"
#include "Composite/Unit/Unit.h"
#include "Component/CollisionComponent/CollisionComponent.h"
#include "../Math/Vec2.h"
SCE_USE

/////////////////////////////////////////////////////////////////////////////////////////
Section::Section(const POINT& _pos, const LONG& _radius) noexcept
    : pimpl{ std::make_unique<impl>(_pos, _radius) }
{
}

/////////////////////////////////////////////////////////////////////////////////////////
Section::~Section()
{
}

/////////////////////////////////////////////////////////////////////////////////////////
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

/////////////////////////////////////////////////////////////////////////////////////////
void Section::CollisionCheck()
{
    if (pimpl->unitList.size() < 2)
        return;

    constexpr float UNIT_RADIUS = 0.5f;

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
                    auto& collisionA = unitA->GetCollision();
                    auto& collisionB = unitB->GetCollision();
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

/////////////////////////////////////////////////////////////////////////////////////////
bool Section::RegisterCollision(const UnitPtr& _unit)
{
    if (_unit == nullptr)
        return false;

    auto& collision = _unit->GetCollision();
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

/////////////////////////////////////////////////////////////////////////////////////////
void Section::UnRegisterCollision(const UnitPtr& _unit)
{
    auto& collision = _unit->GetCollision();
    if (collision != nullptr)
    {
        collision->SetSection(nullptr);
    }
    pimpl->unitList.remove_if([&_unit](auto& target)
    {
        return target.lock() == _unit;
    });
}

/////////////////////////////////////////////////////////////////////////////////////////
void Section::ClearCollisionList()
{
    pimpl->unitList.clear();
}
