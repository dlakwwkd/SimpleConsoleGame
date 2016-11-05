#pragma once
class Unit;


class Section : public std::enable_shared_from_this<Section>
{
    SPECIALFUNC_SET(Section, default)
    enum Direction
    {
        LEFT,
        TOP,
        RIGHT,
        BOTTOM,
        DIR_NUM
    };
    using SectionPtr        = std::shared_ptr<Section>;
    using SectionRef        = std::weak_ptr<Section>;
    using UnitPtr           = std::shared_ptr<Unit>;
    using UnitRef           = std::weak_ptr<Unit>;
    using NearbySections    = std::array<SectionRef, DIR_NUM>;
public:
    Section(const POINT& pos, const LONG& radius);
    ~Section() = default;

    bool        RegisterUnit(const UnitPtr& unit);
    void        UnRegisterUnit(const UnitPtr& unit);
    void        ClearUnitList();

private:
    bool        RegisterUnit(const UnitPtr& unit, Direction dir);
    SectionPtr  BuildNewSection(Direction dir) const;

private:
    POINT               m_CenterPos;
    LONG                m_Radius;
    RECT                m_Boundary;
    NearbySections      m_NearbySections;
    std::list<UnitRef>  m_UnitList;
};
