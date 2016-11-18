#include "stdafx.h"
#include "SkillBasicAttack2.h"
#include "Core/Timer/Timer.h"
#include "Core/Game/Component/RenderComponent/CmdRenderComponent.h"
#include "Core/Game/GameManager.h"
#include "Core/ObjectPool/ObjectPool.h"
#include "../GameObject/Unit.h"
#include "../GameObject/Unit/Missile.h"
#include "../Game.h"
SCE_USE


SkillBasicAttack2::SkillBasicAttack2()
{
    SetDuration(State::COOLTIME, 0.3f);
}

void SkillBasicAttack2::OnPrepare(float dt)
{
}

void SkillBasicAttack2::OnBeginUse()
{
    auto owner = GetOwner<Unit>();
    if (owner == nullptr)
        return;

    auto missile = ObjectPool<Missile>::Get();
    auto render = missile->GetComponent<CmdRenderComponent>();
    if (render == nullptr)
        return;

    render->SetShape(Shape(L'●', Color::WHITE));
    missile->SetDamage(60);
    missile->SetMaxHp(20);
    missile->InitHp();
    missile->SetAttackMask(owner->GetAttackMask());
    missile->SetHitMask(owner->GetHitMask());
    missile->SetPos(owner->GetPos());
    missile->SetSpeed(50.f);
    missile->SetMovePowerFrict(1.5f);
    missile->AddMovePower(owner->GetDirection());

    static auto& gm = GameManager::GetInstance();
    auto& game = gm.GetGame<Game>();
    game.RegisterCollision(missile, owner->GetSection());
    gm.CallFuncAfterP(2.f, missile, &Missile::Death);
}

void SkillBasicAttack2::OnUsing(float dt)
{
}

void SkillBasicAttack2::OnEndUse()
{
}
