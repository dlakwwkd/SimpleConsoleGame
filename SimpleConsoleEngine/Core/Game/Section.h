#pragma once
SCE_START
class Unit;


class Section : public std::enable_shared_from_this<Section>
{
    DECLARE_PIMPL
    enum Direction
    {
        LEFT,
        TOP,
        RIGHT,
        BOTTOM,
        DIR_END
    };
    using UnitPtr			= std::shared_ptr<Unit>;
    using UnitRef			= std::weak_ptr<Unit>;
    using SectionPtr        = std::shared_ptr<Section>;
    using SectionRef        = std::weak_ptr<Section>;
    using NearbySections    = std::array<SectionRef, DIR_END>;
public:
    Section(const POINT& _pos, const LONG& _radius) noexcept;
    ~Section();

    void    SyncCollision(const UnitPtr& _unit);
    void    CollisionCheck();

    bool    RegisterCollision(const UnitPtr& _unit);
    void    UnRegisterCollision(const UnitPtr& _unit);
    void    ClearCollisionList();
};

SCE_END
