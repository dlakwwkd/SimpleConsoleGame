#include "stdafx.h"
#include "Section.h"
#include "GameManager.h"
#include "Interface/ICollision.h"
#include "../ObjectPool/ObjectPool.h"
SCE_START


Section::Section(const POINT& pos, const LONG& radius) noexcept
    : m_CenterPos(pos)
    , m_Radius(radius)
{
    m_Boundary.left = pos.x - radius;
    m_Boundary.top = pos.y - radius;
    m_Boundary.right = pos.x + radius;
    m_Boundary.bottom = pos.y + radius;
}


void Section::SyncCollision(const CollisionPtr& obj)
{
    if (obj == nullptr)
        return;

    Direction dir;
    if (IsOutOfBoundary(obj, dir))
    {
        UnRegisterCollision(obj);
        RegisterCollision(obj, dir);
    }
}

void Section::CollisionCheck()
{
    if (m_CollisionList.size() < 2)
        return;

    const float UNIT_RADIUS = 0.5f;
    auto iterEnd = m_CollisionList.end();
    --iterEnd;
    for (auto iter = m_CollisionList.begin(); iter != iterEnd;)
    {
        if (auto unitA = (*iter).lock())
        {
            auto iter2 = iter;
            ++iter2;
            for (; iter2 != m_CollisionList.end(); ++iter2)
            {
                if (auto unitB = (*iter2).lock())
                {
                    if (ICollision::IsCollisionAble(unitA, unitB))
                    {
                        const Vec2 posA = unitA->GetPos();
                        const Vec2 posB = unitB->GetPos();
                        if (posA.GetX() + UNIT_RADIUS > posB.GetX() - UNIT_RADIUS &&
                            posA.GetX() - UNIT_RADIUS < posB.GetX() + UNIT_RADIUS &&
                            posA.GetY() - UNIT_RADIUS < posB.GetY() + UNIT_RADIUS &&
                            posA.GetY() + UNIT_RADIUS > posB.GetY() - UNIT_RADIUS)
                        {
                            if (unitA->CanAttack(unitB))
                            {
                                unitB->Hitted(unitA->GetDamage());
                            }
                            if (unitB->CanAttack(unitA))
                            {
                                unitA->Hitted(unitB->GetDamage());
                            }
                        }
                    }
                }
            }
            ++iter;
            continue;
        }
        // 유닛이 존재하지 않으면 리스트에서 지운다.
        iter = m_CollisionList.erase(iter);
    }
}


bool Section::RegisterCollision(const CollisionPtr& obj)
{
    if (obj == nullptr)
        return false;

    Direction dir;
    if (IsOutOfBoundary(obj, dir))
    {
        // 유닛이 바운더리 바깥이면 해당 방향의 섹션에 등록을 시도한다.
        return RegisterCollision(obj, dir);
    }
    // 유닛 리스트에 등록하고, 유닛에게 등록된 섹션을 알려준다.
    m_CollisionList.push_back(obj);
    obj->SetSection(shared_from_this());
    return true;
}

void Section::UnRegisterCollision(const CollisionPtr& obj)
{
    obj->SetSection(nullptr);
    m_CollisionList.remove_if([&obj](auto& target)
    {
        return target.lock() == obj;
    });
}

void Section::ClearCollisionList()
{
    m_CollisionList.clear();
}


bool Section::IsOutOfBoundary(const CollisionPtr& obj, OUT Direction& dir)
{
    auto x = obj->GetPos().GetX();
    auto y = obj->GetPos().GetY();
    if (x < m_Boundary.left)
    {
        dir = Direction::LEFT;
        return true;
    }
    if (y < m_Boundary.top)
    {
        dir = Direction::TOP;
        return true;
    }
    if (x > m_Boundary.right)
    {
        dir = Direction::RIGHT;
        return true;
    }
    if (y > m_Boundary.bottom)
    {
        dir = Direction::BOTTOM;
        return true;
    }
    return false;
}

bool Section::RegisterCollision(const CollisionPtr& obj, Direction dir)
{
    // 해당 방향에 섹션이 존재하면, 바로 등록을 시도한다.
    if (auto section = m_NearbySections[dir].lock())
    {
        return section->RegisterCollision(obj);
    }
    // 섹션이 존재하지 않으면, 새롭게 생성하고, 등록을 시도한다.
    auto newSection = BuildSection(dir);
    if (newSection == nullptr)
        return false;

    return newSection->RegisterCollision(obj);
}

Section::SectionPtr Section::BuildSection(Direction dir) const
{
    // 1. 생성할 위치 계산
    auto createPos = m_CenterPos;
    auto diameter = m_Radius * 2;
    switch (dir)
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
    auto newSection = ObjectPool<Section>::Get(createPos, m_Radius);
    gm.RegisterBuiltSection(newSection, createPos);

    // 4. 주변 섹션들과 연결
    if (auto left = gm.FindSection({ createPos.x - diameter, createPos.y }))
    {
        newSection->m_NearbySections[Direction::LEFT] = left;
        left->m_NearbySections[Direction::RIGHT] = newSection;
    }
    if (auto top = gm.FindSection({ createPos.x, createPos.y - diameter }))
    {
        newSection->m_NearbySections[Direction::TOP] = top;
        top->m_NearbySections[Direction::BOTTOM] = newSection;
    }
    if (auto right = gm.FindSection({ createPos.x + diameter, createPos.y }))
    {
        newSection->m_NearbySections[Direction::RIGHT] = right;
        right->m_NearbySections[Direction::LEFT] = newSection;
    }
    if (auto bottom = gm.FindSection({ createPos.x, createPos.y + diameter }))
    {
        newSection->m_NearbySections[Direction::BOTTOM] = bottom;
        bottom->m_NearbySections[Direction::TOP] = newSection;
    }
    return newSection;
}

SCE_END
