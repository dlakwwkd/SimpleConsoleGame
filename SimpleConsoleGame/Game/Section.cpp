#include "stdafx.h"
#include "Section.h"
#include "Game.h"
#include "Core/Game/GameManager.h"
#include "GameObject/Unit.h"


Section::Section(const POINT& pos, const LONG& radius)
:   m_CenterPos(pos),
    m_Radius(radius)
{
    m_Boundary.left = pos.x - radius;
    m_Boundary.top = pos.y - radius;
    m_Boundary.right = pos.x + radius;
    m_Boundary.bottom = pos.y + radius;
}

void Section::SyncUnit(const UnitPtr& unit)
{
    if (unit == nullptr)
        return;

    Direction dir;
    if (IsOutOfBoundary(unit, dir))
    {
        UnRegisterUnit(unit);
        RegisterUnit(unit, dir);
    }
}

void Section::CollisionCheck()
{
    if (m_UnitList.size() < 2)
        return;

    const float UNIT_RADIUS = 0.5f;
    auto iterEnd = m_UnitList.end();
    --iterEnd;
    for (auto iter = m_UnitList.begin(); iter != iterEnd;)
    {
        if (auto unitA = (*iter).lock())
        {
            auto iter2 = iter;
            ++iter2;
            for (; iter2 != m_UnitList.end(); ++iter2)
            {
                if (auto unitB = (*iter2).lock())
                {
                    if (Unit::IsCollisionAble(unitA, unitB))
                    {
                        const float xA = unitA->GetPos().GetX();
                        const float yA = unitA->GetPos().GetY();
                        const float xB = unitB->GetPos().GetX();
                        const float yB = unitB->GetPos().GetY();
                        if (xA + UNIT_RADIUS > xB - UNIT_RADIUS &&
                            xA - UNIT_RADIUS < xB + UNIT_RADIUS &&
                            yA - UNIT_RADIUS < yB + UNIT_RADIUS &&
                            yA + UNIT_RADIUS > yB - UNIT_RADIUS)
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
        iter = m_UnitList.erase(iter);
    }
}



bool Section::RegisterUnit(const UnitPtr& unit)
{
    if (unit == nullptr)
        return false;

    Direction dir;
    if (IsOutOfBoundary(unit, dir))
    {
        // 유닛이 바운더리 바깥이면 해당 방향의 섹션에 등록을 시도한다.
        return RegisterUnit(unit, dir);
    }
    // 유닛 리스트에 등록하고, 유닛에게 등록된 섹션을 알려준다.
    m_UnitList.push_back(unit);
    unit->SetSection(shared_from_this());
    return true;
}

void Section::UnRegisterUnit(const UnitPtr& unit)
{
    unit->SetSection(nullptr);
    m_UnitList.remove_if([&unit](auto& target)
    {
        return target.lock() == unit;
    });
}

void Section::ClearUnitList()
{
    m_UnitList.clear();
}



bool Section::IsOutOfBoundary(const UnitPtr& unit, OUT Direction& dir)
{
    auto x = unit->GetPos().GetX();
    auto y = unit->GetPos().GetY();
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

bool Section::RegisterUnit(const UnitPtr& unit, Direction dir)
{
    // 해당 방향에 섹션이 존재하면, 바로 등록을 시도한다.
    if (auto section = m_NearbySections[dir].lock())
    {
        return section->RegisterUnit(unit);
    }
    // 섹션이 존재하지 않으면, 새롭게 생성하고, 등록을 시도한다.
    auto newSection = BuildSection(dir);
    if (newSection == nullptr)
        return false;

    return newSection->RegisterUnit(unit);
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
    auto& game = SCE::GameManager::GetInstance().GetGame<Game>();
    auto exist = game.FindSection(createPos);
    if (exist != nullptr)
        return exist;

    // 3. 새로 섹션을 생성한 후 게임에 등록 (유일한 shared count)
    auto newSection = std::make_shared<Section>(createPos, m_Radius);
    game.RegisterBuiltSection(newSection, createPos);

    // 4. 주변 섹션들과 연결
    if (auto left = game.FindSection({ createPos.x - diameter, createPos.y }))
    {
        newSection->m_NearbySections[Direction::LEFT] = left;
        left->m_NearbySections[Direction::RIGHT] = newSection;
    }
    if (auto top = game.FindSection({ createPos.x, createPos.y - diameter }))
    {
        newSection->m_NearbySections[Direction::TOP] = top;
        top->m_NearbySections[Direction::BOTTOM] = newSection;
    }
    if (auto right = game.FindSection({ createPos.x + diameter, createPos.y }))
    {
        newSection->m_NearbySections[Direction::RIGHT] = right;
        right->m_NearbySections[Direction::LEFT] = newSection;
    }
    if (auto bottom = game.FindSection({ createPos.x, createPos.y + diameter }))
    {
        newSection->m_NearbySections[Direction::BOTTOM] = bottom;
        bottom->m_NearbySections[Direction::TOP] = newSection;
    }
    return newSection;
}
