#include "stdafx.h"
#include "SkillBasicAttackSwap.h"
#include "Core/Timer/Timer.h"
#include "Core/Game/Component/RenderComponent/CmdRenderComponent.h"
#include "Core/Game/GameManager.h"
#include "../GameObject/Unit.h"
#include "../GameObject/Unit/Missile.h"
#include "../GameObject/Unit/Hero.h"
#include "../Game.h"
SCE_USE


SkillBasicAttackSwap::SkillBasicAttackSwap()
:   m_CurIdx(0)
{
    SetDuration(State::COOLTIME, 0.5f);
}

void SkillBasicAttackSwap::OnPrepare(float dt)
{
}

void SkillBasicAttackSwap::OnBeginUse()
{
    auto owner = GetOwner<Hero>();
    if (owner == nullptr)
        return;

    // 매우 구린 하드코딩이지만, 일단 이렇게 구현
    if (++m_CurIdx > 3)
    {
        m_CurIdx = 0;
    }
    owner->SwapMissile(m_CurIdx);
}

void SkillBasicAttackSwap::OnUsing(float dt)
{
}

void SkillBasicAttackSwap::OnEndUse()
{
}
