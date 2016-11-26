#pragma once
#include "Core/Game/Skill.h"


class SkillBasicAttack : public SCE::Skill
{
    SPECIALFUNC_MOVE_SET(SkillBasicAttack, default)
public:
    SkillBasicAttack();
    virtual ~SkillBasicAttack() = default;
    
    virtual void    OnPrepare(float _dt)    override;
    virtual void    OnBeginUse()            override;
    virtual void    OnUsing(float _dt)      override;
    virtual void    OnEndUse()              override;
};
