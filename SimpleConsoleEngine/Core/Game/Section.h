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
    using ObjectPtr			= std::shared_ptr<Unit>;
    using ObjectRef			= std::weak_ptr<Unit>;
    using SectionPtr        = std::shared_ptr<Section>;
    using SectionRef        = std::weak_ptr<Section>;
    using NearbySections    = std::array<SectionRef, DIR_END>;
public:
    Section(const POINT& _pos, const LONG& _radius) noexcept;
    ~Section();

    void    SyncCollision(const ObjectPtr& _obj);
    void    CollisionCheck();

    bool    RegisterCollision(const ObjectPtr& _obj);
    void    UnRegisterCollision(const ObjectPtr& _obj);
    void    ClearCollisionList();
};

SCE_END
