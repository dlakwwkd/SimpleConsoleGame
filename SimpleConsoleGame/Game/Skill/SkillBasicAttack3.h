#pragma once
#include "Core/Game/Skill.h"


class SkillBasicAttack3 : public SCE::Skill
{
    SPECIALFUNC_MOVE_SET(SkillBasicAttack3, default)
public:
    SkillBasicAttack3();
    virtual ~SkillBasicAttack3() = default;
    
    virtual void    OnPrepare(float _dt)    override;
    virtual void    OnBeginUse()            override;
    virtual void    OnUsing(float _dt)      override;
    virtual void    OnEndUse()              override;
};
