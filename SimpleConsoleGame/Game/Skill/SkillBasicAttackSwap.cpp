#include "stdafx.h"
#include "SkillBasicAttackSwap.h"
#include "../GameObject/Unit/Hero.h"
SCE_USE


SkillBasicAttackSwap::SkillBasicAttackSwap()
    : curIdx{}
{
    SetDuration(State::COOLTIME, 0.5f);
}


void SkillBasicAttackSwap::OnPrepare(float _dt)
{
}

void SkillBasicAttackSwap::OnBeginUse()
{
    auto owner = GetOwner<Hero>();
    if (owner == nullptr)
        return;

    // 매우 구린 하드코딩이지만, 일단 이렇게 구현
    if (++curIdx > 3)
    {
        curIdx = 0;
    }
    owner->SwapMissile(curIdx);
}

void SkillBasicAttackSwap::OnUsing(float _dt)
{
}

void SkillBasicAttackSwap::OnEndUse()
{
}
