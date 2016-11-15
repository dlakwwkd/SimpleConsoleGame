#pragma once
#include "../Skill.h"


class SkillBasicAttack2 : public Skill
{
    SPECIALFUNC_SET(SkillBasicAttack2, default)
public:
    SkillBasicAttack2();
    virtual ~SkillBasicAttack2() = default;
    
    virtual void    OnPrepare(float dt) override;
    virtual void    OnBeginUse()        override;
    virtual void    OnUsing(float dt)   override;
    virtual void    OnEndUse()          override;
};
