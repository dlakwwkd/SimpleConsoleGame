#include "stdafx.h"
#include "Section.h"
#include "GameObject/Unit.h"


Section::Section(const POINT& pos, const LONG& radius)
:   m_CenterPos(pos),
    m_Radius(radius),
    m_IsChecked(false)
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
    m_IsChecked = false;
}

void Section::CollisionCheck()
{
    if (m_IsChecked)
        return;

    m_IsChecked = true;
    if (m_UnitList.size() > 1)
    {
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
    for (auto& sectionRef : m_NearbySections)
    {
        if (auto section = sectionRef.lock())
        {
            // 주변 섹션을 순회하면서 충돌체크를 실시한다.
            // 이미 체크를 시행한 섹션은 m_IsChecked가 true이므로 생략하기 때문에
            // 중복체크는 하지 않으며, m_IsChecked의 초기화는 다음 프레임에서
            // SyncUnit()을 통해 이루어진다.
            section->CollisionCheck();
        }
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
    // 섹션끼리는 weak_ptr만 들고있기 때문에, 여기서 유닛에게 보관시키는
    // shared_ptr이 유효 카운트이다.
    // 즉, 이 섹션에 포함된 유닛이 0이 될때, 자동으로 이 섹션도 파괴된다.
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
    auto newSection = BuildNewSection(dir);
    if (newSection != nullptr)
    {
        auto oppositeDir = GetOppositeDir(dir);
        newSection->m_NearbySections[oppositeDir] = shared_from_this();
        m_NearbySections[dir] = newSection;
        return newSection->RegisterUnit(unit);
    }
    return false;
}

Section::SectionPtr Section::BuildNewSection(Direction dir) const
{
    // 1. 생성하려는 위치에 이미 섹션이 있으면 해당 섹션 리턴
    // 2. 생성하려는 위치 주변에 섹션이 있으면 연결할 수 있게 포인터 저장
    std::vector<std::tuple<Direction, Direction, SectionPtr>> needLinkSections;
    auto Function = [&](Direction side1, Direction side2) -> SectionPtr
    {
        if (auto nearSection = m_NearbySections[side1].lock())
        {
            if (auto diagonal = nearSection->m_NearbySections[dir].lock())
            {
                if (auto exist = diagonal->m_NearbySections[side2].lock())
                {
                    return exist;
                }
                needLinkSections.push_back(std::make_tuple(side1, side2, diagonal));
            }
        }
        if (auto nearSection = m_NearbySections[side2].lock())
        {
            if (auto diagonal = nearSection->m_NearbySections[dir].lock())
            {
                if (auto exist = diagonal->m_NearbySections[side1].lock())
                {
                    return exist;
                }
                needLinkSections.push_back(std::make_tuple(side2, side1, diagonal));
            }
        }
        return nullptr;
    };
    switch (dir)
    {
    case Direction::LEFT:
    case Direction::RIGHT:
        {
            auto exist = Function(TOP, BOTTOM);
            if (exist != nullptr)
                return exist;
        }
        break;
    case Direction::TOP:
    case Direction::BOTTOM:
        {
            auto exist = Function(LEFT, RIGHT);
            if (exist != nullptr)
                return exist;
        }
        break;
    }

    // 3. 생성할 위치 계산
    auto createPos = m_CenterPos;
    switch (dir)
    {
    case Direction::LEFT:    createPos.x -= m_Radius * 2; break;
    case Direction::TOP:     createPos.y -= m_Radius * 2; break;
    case Direction::RIGHT:   createPos.x += m_Radius * 2; break;
    case Direction::BOTTOM:  createPos.y += m_Radius * 2; break;
    }

    // 4. 생성 후 주변 섹션들과 연결
    auto newSection = std::make_shared<Section>(createPos, m_Radius);
    Direction side1, side2;
    SectionPtr target;
    for (auto sectionInfo : needLinkSections)
    {
        std::tie(side1, side2, target) = sectionInfo;
        newSection->m_NearbySections[side1] = target;
        target->m_NearbySections[side2] = newSection;
    }
    return newSection;
}

Section::Direction Section::GetOppositeDir(Direction dir) const
{
    switch (dir)
    {
    case Direction::LEFT:    return Direction::RIGHT;
    case Direction::TOP:     return Direction::BOTTOM;
    case Direction::RIGHT:   return Direction::LEFT;
    case Direction::BOTTOM:  return Direction::TOP;
    default:
        return Direction::DIR_END;
    }
}
