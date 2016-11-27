#pragma once
#include "../GameObject.h"
#include "../../Interface/Object/IRenderObject.h"
#include "../../Interface/Object/ICollisionObject.h"
SCE_START
class Skill;


class Unit
    : public IRenderObject
    , public ICollisionObject
    , public GameObject
{
    DECLARE_PIMPL
    SPECIALFUNC_MOVE_SET(Unit, default)
    using UnitPtr   = std::shared_ptr<Unit>;
    using SkillPtr  = std::shared_ptr<Skill>;
    using SkillList = std::vector<SkillPtr>;
public:
    Unit() noexcept;
    virtual ~Unit() override;

    virtual void            Init() override;
    virtual void            Release() override;
    virtual void            Update(float _dt) override;

    virtual RenderPtr       GetRender() override;
    virtual void            Render() override;

    virtual CollisionPtr    GetCollision() override;
    virtual bool            Hitted(int _damage) override;
    virtual void            Death() override;

    void                    AddSkill(const SkillPtr& _skill);
    SkillList&              GetSkillList();
};

SCE_END
