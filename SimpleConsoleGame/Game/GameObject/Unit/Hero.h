#pragma once
#include "../Unit.h"
class Skill;


class Hero : public Unit
{
    SPECIALFUNC_SET(Hero, default)
    using SkillPtr = std::shared_ptr<Skill>;
public:
    Hero();
    virtual ~Hero() override;

    virtual void    Init()             override;
    virtual void    Release()          override;
    virtual void    Update(float dt)   override;
    virtual void    Render()           override;

    void            SetDefaultAttack(const SkillPtr& skill);
    void            ShootMissile();

private:
    SkillPtr        m_DefaultAttack;
};
