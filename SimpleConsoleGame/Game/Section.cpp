#include "stdafx.h"
#include "Section.h"
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

bool Section::RegisterUnit(const UnitPtr& unit)
{
    if (unit == nullptr)
        return false;

    auto x = unit->GetPos().GetX();
    auto y = unit->GetPos().GetY();
    if (x < m_Boundary.left)
    {
        return RegisterUnit(unit, Direction::LEFT);
    }
    if (y < m_Boundary.top)
    {
        return RegisterUnit(unit, Direction::TOP);
    }
    if (x > m_Boundary.right)
    {
        return RegisterUnit(unit, Direction::RIGHT);
    }
    if (y > m_Boundary.bottom)
    {
        return RegisterUnit(unit, Direction::BOTTOM);
    }
    unit->SetSection(shared_from_this());
    m_UnitList.push_back(unit);
    return true;
}

void Section::UnRegisterUnit(const UnitPtr& unit)
{
    m_UnitList.remove_if([&unit](auto& target)
    {
        return target.lock() == unit;
    });
}

void Section::ClearUnitList()
{
    m_UnitList.clear();
}



bool Section::RegisterUnit(const UnitPtr& unit, Direction dir)
{
    if (auto section = m_NearbySections[dir].lock())
    {
        return section->RegisterUnit(unit);
    }
    auto newSection = BuildNewSection(dir);
    if (newSection == nullptr)
        return false;

    m_NearbySections[dir] = newSection;
    return newSection->RegisterUnit(unit);
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
