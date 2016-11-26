#pragma once
#include "Core/Game/Skill.h"


class SkillBasicAttackSwap : public SCE::Skill
{
    SPECIALFUNC_MOVE_SET(SkillBasicAttackSwap, default)
public:
    SkillBasicAttackSwap();
    virtual ~SkillBasicAttackSwap() = default;
    
    virtual void    OnPrepare(float _dt)    override;
    virtual void    OnBeginUse()            override;
    virtual void    OnUsing(float _dt)      override;
    virtual void    OnEndUse()              override;

private:
    int             curIdx;
};
