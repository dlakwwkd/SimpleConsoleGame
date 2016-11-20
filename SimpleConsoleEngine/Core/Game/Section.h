#pragma once
SCE_START
class ICollision;


class Section : public std::enable_shared_from_this<Section>
{
    enum Direction
    {
        LEFT,
        TOP,
        RIGHT,
        BOTTOM,
        DIR_END
    };
    using SectionPtr        = std::shared_ptr<Section>;
    using SectionRef        = std::weak_ptr<Section>;
    using CollisionPtr      = std::shared_ptr<ICollision>;
    using CollisionRef      = std::weak_ptr<ICollision>;
    using NearbySections    = std::array<SectionRef, DIR_END>;
public:
    Section(const POINT& pos, const LONG& radius) noexcept;

    void        SyncCollision(const CollisionPtr& obj);
    void        CollisionCheck();

    bool        RegisterCollision(const CollisionPtr& obj);
    void        UnRegisterCollision(const CollisionPtr& obj);
    void        ClearCollisionList();

private:
    bool        IsOutOfBoundary(const CollisionPtr& obj, OUT Direction& dir);
    bool        RegisterCollision(const CollisionPtr& obj, Direction dir);
    SectionPtr  BuildSection(Direction dir) const;

private:
    POINT                   m_CenterPos;
    LONG                    m_Radius;
    RECT                    m_Boundary;
    NearbySections          m_NearbySections;
    std::list<CollisionRef> m_CollisionList;
};

SCE_END
