#pragma once
#include "../../Interface/Object/IRenderObject.h"
#include "../../Interface/Object/ICollisionObject.h"
#include "../GameObject.h"
SCE_START
class Skill;
class CmdRenderComponent;
class CollisionComponent;

/////////////////////////////////////////////////////////////////////////////////////////
class Unit
    : public IRenderObject
    , public ICollisionObject
    , public GameObject
{
    DECLARE_PIMPL
    SPECIALFUNC_MOVE_SET(Unit, default)
    using UnitPtr       = std::shared_ptr<Unit>;
    using SkillPtr      = std::shared_ptr<Skill>;
    using SkillList     = std::vector<SkillPtr>;
    using RenderPtr     = std::shared_ptr<CmdRenderComponent>;
    using CollisionPtr  = std::shared_ptr<CollisionComponent>;
public:
    Unit() noexcept;
    virtual ~Unit() override;

    virtual void            Init() override;
    virtual void            Release() override;
    virtual void            Update(float _dt) override;
    virtual void            Render() override;

    virtual bool            Hitted(int _damage) override;
    virtual void            Death() override;
    virtual void            SetDeathEffect(EffectType _type) override;

protected:
    void                    AddSkill(const SkillPtr& _skill);
    SkillList&              GetSkillList();

public:
    const RenderPtr&        GetRender() const { return render; }
    const CollisionPtr&     GetCollision() const { return collision; }

private:
    RenderPtr               render;
    CollisionPtr            collision;
};

SCE_END
