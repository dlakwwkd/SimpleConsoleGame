#pragma once
#include "../Skill.h"


class SkillBasicAttackSwap : public Skill
{
    SPECIALFUNC_SET(SkillBasicAttackSwap, default)
public:
    SkillBasicAttackSwap();
    virtual ~SkillBasicAttackSwap() = default;
    
    virtual void    OnPrepare(float dt) override;
    virtual void    OnBeginUse()        override;
    virtual void    OnUsing(float dt)   override;
    virtual void    OnEndUse()          override;

private:
    int             m_CurIdx;
};
