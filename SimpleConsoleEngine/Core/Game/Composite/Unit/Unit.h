#pragma once
#include "../GameObject.h"
#include "../../Interface/ICollision.h"
SCE_START
class IRenderComponent;
class ICollisionComponent;
class Section;
class Skill;


class Unit
    : public ICollision
    , public GameObject
{
    SPECIALFUNC_SET(Unit, default)
    using UnitPtr       = std::shared_ptr<Unit>;
    using SkillPtr      = std::shared_ptr<Skill>;
    using SkillList     = std::vector<SkillPtr>;
    using RenderRef     = std::weak_ptr<IRenderComponent>;
    using CollisionRef  = std::weak_ptr<ICollisionComponent>;
public:
    Unit() noexcept;
    virtual ~Unit() override;

    virtual void            Init() override;
    virtual void            Release() override;
    virtual void            Update(float dt) override;
    virtual void            Render() override;

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

public:
    void                    AddSkill(const SkillPtr& skill);

protected:
    SkillList               m_SkillList;
    RenderRef               m_Render;
    CollisionRef            m_Collision;
    bool                    m_HitRenderFlag;
};

SCE_END
