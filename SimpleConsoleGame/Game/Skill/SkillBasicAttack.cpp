#include "stdafx.h"
#include "SkillBasicAttack.h"
#include "Core/Timer/Timer.h"
#include "../GameObject/Unit.h"
SCE_USE


SkillBasicAttack::SkillBasicAttack()
{
    SetDuration(State::COOLTIME, 0.3f);
}

void SkillBasicAttack::OnPrepare(float dt)
{
}

void SkillBasicAttack::OnBeginUse()
{
    // TODO: 여기서 미사일 쏘는 것만 구현하면 됨.
}

void SkillBasicAttack::OnUsing(float dt)
{
}

void SkillBasicAttack::OnEndUse()
{
}
