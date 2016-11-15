#include "stdafx.h"
#include "SkillBasicAttack3.h"
#include "Core/Timer/Timer.h"
#include "Core/Game/Component/RenderComponent/CmdRenderComponent.h"
#include "Core/Game/GameManager.h"
#include "../GameObject/Unit.h"
#include "../GameObject/Unit/Missile.h"
#include "../Game.h"
SCE_USE


SkillBasicAttack3::SkillBasicAttack3()
{
    SetDuration(State::COOLTIME, 0.01f);
}

void SkillBasicAttack3::OnPrepare(float dt)
{
}

void SkillBasicAttack3::OnBeginUse()
{
    auto owner = GetOwner<Unit>();
    if (owner == nullptr)
        return;

    auto missile = std::make_shared<Missile>();
    auto render = missile->GetComponent<CmdRenderComponent>();
    if (render == nullptr)
        return;

    render->SetShape(Shape(L'x', Color::MAGENTA));
    missile->SetDamage(10);
    missile->SetMaxHp(1);
    missile->InitHp();
    missile->SetAttackMask(owner->GetAttackMask());
    missile->SetHitMask(owner->GetHitMask());
    missile->SetPos(owner->GetPos());
    missile->SetSpeed(100.0f);
    missile->SetMovePowerFrict(0.0f);
    missile->AddMovePower(owner->GetDirection());
    GameManager::GetInstance().GetGame<Game>().RegisterCollision(missile, owner->GetSection());
}

void SkillBasicAttack3::OnUsing(float dt)
{
}

void SkillBasicAttack3::OnEndUse()
{
}
