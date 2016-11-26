#pragma once
#include "../../Interface/Component/ICollisionComponent.h"
SCE_START
class Section;


class CollisionComponent : public ICollisionComponent
{
    DECLARE_PIMPL
    SPECIALFUNC_MOVE_SET(CollisionComponent, default)
    using CollsionPtr   = std::shared_ptr<CollisionComponent>;
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
    static bool             IsCollisionAble(const CollsionPtr& _a, const CollsionPtr& _b)
    {
        if (_a == nullptr || _b == nullptr)
            return false;

        return _a->GetHitMask() & _b->GetAttackMask()
            || _b->GetHitMask() & _a->GetAttackMask();
    }
public:
    CollisionComponent(const CompositeRef& _owner) noexcept;
    virtual ~CollisionComponent() override;

    virtual std::string     GetComponentName() const override;
    virtual CompositePtr    GetOwner() const override;

    bool                    Hitted(int _damage);
    void                    Death();

    bool                    IsDeath() const;
    bool                    CanAttack(const CollsionPtr& _target) const;

    int                     GetCurHp() const;
    int                     GetMaxHp() const;
    int                     GetDamage() const;
    SectionPtr              GetSection() const;
    CollisionMask           GetHitMask() const;
    CollisionMask           GetAttackMask() const;

    void                    InitHp();
    void                    SetMaxHp(int _maxHp);
    void                    SetDamage(int _damage);
    void                    SetSection(const SectionPtr& _section);
    void                    SetHitMask(CollisionMask _mask);
    void                    SetAttackMask(CollisionMask _mask);
    void                    SetHitLock(bool _lock);
};

SCE_END
