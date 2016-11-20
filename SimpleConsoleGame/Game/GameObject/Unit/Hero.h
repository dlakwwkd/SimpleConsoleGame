#pragma once
#include "Core/Game/Composite/Unit/Unit.h"
SCE_START
class Skill;
SCE_END


class Hero : public SCE::Unit
{
    SPECIALFUNC_SET(Hero, default)
    using SkillPtr = std::shared_ptr<SCE::Skill>;
public:
    Hero() noexcept;
    virtual ~Hero() override;

    virtual void    Init()             override;
    virtual void    Release()          override;
    virtual void    Update(float dt)   override;
    virtual void    Render()           override;

    void            SetDefaultAttack();
    void            ShootMissile();
    void            SwapMissile();
    void            SwapMissile(int idx);

private:
    SkillPtr        m_DefaultAttack;
    SkillPtr        m_MissileSwap;
};
