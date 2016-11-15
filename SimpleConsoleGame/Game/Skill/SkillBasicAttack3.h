#pragma once
#include "../Skill.h"


class SkillBasicAttack3 : public Skill
{
    SPECIALFUNC_SET(SkillBasicAttack3, default)
public:
    SkillBasicAttack3();
    virtual ~SkillBasicAttack3() = default;
    
    virtual void    OnPrepare(float dt) override;
    virtual void    OnBeginUse()        override;
    virtual void    OnUsing(float dt)   override;
    virtual void    OnEndUse()          override;
};
