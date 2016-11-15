#include "stdafx.h"
#include "SkillBasicAttack.h"
#include "Core/Timer/Timer.h"
#include "Core/Game/Component/RenderComponent/CmdRenderComponent.h"
#include "Core/Game/GameManager.h"
#include "../GameObject/Unit.h"
#include "../GameObject/Unit/Missile.h"
#include "../Game.h"
SCE_USE


SkillBasicAttack::SkillBasicAttack()
{
    SetDuration(State::COOLTIME, 0.1f);
}

void SkillBasicAttack::OnPrepare(float dt)
{
}

void SkillBasicAttack::OnBeginUse()
{
    auto owner = GetOwner<Unit>();
    if (owner == nullptr)
        return;

    auto missile = std::make_shared<Missile>();
    auto render = missile->GetComponent<CmdRenderComponent>();
    if (render == nullptr)
        return;

    render->SetShape(Shape(L'o', Color::BLUE));
    missile->SetDamage(10);
    missile->SetMaxHp(1);
    missile->InitHp();
    missile->SetAttackMask(owner->GetAttackMask());
    missile->SetHitMask(owner->GetHitMask());
    missile->SetPos(owner->GetPos());
    missile->SetSpeed(80.0f);
    missile->SetMovePowerFrict(0.0f);
    missile->AddMovePower(owner->GetDirection());
    GameManager::GetInstance().GetGame<Game>().RegisterCollision(missile, owner->GetSection());
}

void SkillBasicAttack::OnUsing(float dt)
{
}

void SkillBasicAttack::OnEndUse()
{
}
