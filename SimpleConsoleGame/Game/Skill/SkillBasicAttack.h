#pragma once
#include "Core/Game/Skill.h"


class SkillBasicAttack : public SCE::Skill
{
    SPECIALFUNC_SET(SkillBasicAttack, default)
public:
    SkillBasicAttack();
    virtual ~SkillBasicAttack() = default;
    
    virtual void    OnPrepare(float dt) override;
    virtual void    OnBeginUse()        override;
    virtual void    OnUsing(float dt)   override;
    virtual void    OnEndUse()          override;
};
