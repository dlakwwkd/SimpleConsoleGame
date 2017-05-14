#pragma once
#include "../../Interface/Component/ICollisionComponent.h"
SCE_START
class Section;

/////////////////////////////////////////////////////////////////////////////////////////
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

    bool                    Hitted(int _damage) noexcept;
    void                    Death() noexcept;
    bool                    IsDeath() const noexcept;
    bool                    CanAttack(const CollsionPtr& _target) const noexcept;

    int                     GetCurHp() const noexcept;
    int                     GetMaxHp() const noexcept;
    int                     GetDamage() const noexcept;
    SectionPtr              GetSection() const noexcept;
    CollisionMask           GetHitMask() const noexcept;
    CollisionMask           GetAttackMask() const noexcept;

    void                    InitHp() noexcept;
    void                    AddHp(int _hp, bool _isWithMax) noexcept;
    void                    SetCurHp(int _hp) noexcept;
    void                    SetMaxHp(int _hp) noexcept;
    void                    SetDamage(int _damage) noexcept;
    void                    SetSection(const SectionPtr& _section) noexcept;
    void                    SetHitMask(CollisionMask _mask) noexcept;
    void                    SetAttackMask(CollisionMask _mask) noexcept;
    void                    SetHitLock(bool _lock) noexcept;
};

SCE_END
