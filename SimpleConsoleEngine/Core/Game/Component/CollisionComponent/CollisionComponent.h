#pragma once
#include "../../Interface/ICollisionComponent.h"
SCE_START


class CollisionComponent : public ICollisionComponent
{
    SPECIALFUNC_SET(CollisionComponent, default)
public:
    CollisionComponent(const CompositeRef& owner) noexcept;
    virtual ~CollisionComponent() override;

    virtual void            Init() override;
    virtual void            Release() override;
    virtual void            Update(float dt) override;

    virtual std::string     GetComponentName() const override;
    virtual CompositePtr    GetOwner() const override;
    virtual IComponentPtr   Copy() const override;

    virtual bool            Hitted(int damage) override;
    virtual void            Death() override;

    virtual bool            IsDeath() const override;
    virtual bool            CanAttack(const CollsionPtr& target) const override;

    virtual int             GetCurHp() const override;
    virtual int             GetMaxHp() const override;
    virtual int             GetDamage() const override;
    virtual Vec2            GetPos() const override;
    virtual SectionPtr      GetSection() const override;
    virtual CollisionMask   GetHitMask() const override;
    virtual CollisionMask   GetAttackMask() const override;

    virtual void            InitHp() override;
    virtual void            SetMaxHp(int maxHp) override;
    virtual void            SetDamage(int damage) override;
    virtual void            SetPos(const Vec2& pos) override;
    virtual void            SetSection(const SectionPtr& section) override;
    virtual void            SetHitMask(CollisionMask mask) override;
    virtual void            SetAttackMask(CollisionMask mask) override;
    virtual void            SetHitLock(bool lock) override;

private:
    CompositeRef            m_Owner;
    SectionRef              m_Section;
    int                     m_MaxHp;
    int                     m_CurHp;
    int                     m_Damage;
    bool                    m_IsDeath;
    bool                    m_HitLock;
    CollisionMask           m_HitMask;      // 맞을 수 있는 공격 종류
    CollisionMask           m_AttackMask;   // 때릴 수 있는 공격 종류

};


SCE_END
