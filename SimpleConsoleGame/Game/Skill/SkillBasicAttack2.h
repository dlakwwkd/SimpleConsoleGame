#pragma once
#include "Core/Game/Skill.h"


class SkillBasicAttack2 : public SCE::Skill
{
    SPECIALFUNC_MOVE_SET(SkillBasicAttack2, default)
public:
    SkillBasicAttack2();
    virtual ~SkillBasicAttack2() = default;
    
    virtual void    OnPrepare(float _dt)    override;
    virtual void    OnBeginUse()            override;
    virtual void    OnUsing(float _dt)      override;
    virtual void    OnEndUse()              override;
};
