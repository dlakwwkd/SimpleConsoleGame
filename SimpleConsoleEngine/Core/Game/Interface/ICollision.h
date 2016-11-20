#pragma once
#include "../Section.h"
#include "../../Math/Vec2.h"
SCE_START


class ICollision
{
    SPECIALFUNC_SET(ICollision, default)
protected:
    using CollsionPtr   = std::shared_ptr<ICollision>;
    using SectionPtr    = std::shared_ptr<Section>;
    using SectionRef    = std::weak_ptr<Section>;
public:
    enum CollisionMask : unsigned char
    {
        NONE    = 0,
        PLAYER  = 1 << 0,
        ENEMY   = 1 << 1,
        ALL     = PLAYER | ENEMY
    };
    static bool             IsCollisionAble(const CollsionPtr& objA, const CollsionPtr& objB)
    {
        if (objA == nullptr || objB == nullptr)
            return false;

        return objA->GetHitMask() & objB->GetAttackMask()
            || objB->GetHitMask() & objA->GetAttackMask();
    }
public:
    ICollision() noexcept {}
    virtual ~ICollision() {}
    
    virtual void            Update(float dt)                            = 0;

    virtual bool            Hitted(int damage)                          = 0;
    virtual void            Death()                                     = 0;

    virtual bool            IsDeath() const                             = 0;
    virtual bool            CanAttack(const CollsionPtr& target) const  = 0;
    
    virtual int             GetCurHp() const                            = 0;
    virtual int             GetMaxHp() const                            = 0;
    virtual int             GetDamage() const                           = 0;
    virtual Vec2            GetPos() const                              = 0;
    virtual SectionPtr      GetSection() const                          = 0;
    virtual CollisionMask   GetHitMask() const                          = 0;
    virtual CollisionMask   GetAttackMask() const                       = 0;

    virtual void            InitHp()                                    = 0;
    virtual void            SetMaxHp(int maxHp)                         = 0;
    virtual void            SetDamage(int damage)                       = 0;
    virtual void            SetPos(const Vec2& pos)                     = 0;
    virtual void            SetSection(const SectionPtr& section)       = 0;
    virtual void            SetHitMask(CollisionMask mask)              = 0;
    virtual void            SetAttackMask(CollisionMask mask)           = 0;
    virtual void            SetHitLock(bool lock)                       = 0;
};

SCE_END
