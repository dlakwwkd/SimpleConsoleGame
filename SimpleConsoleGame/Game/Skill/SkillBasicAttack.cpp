#include "stdafx.h"
#include "SkillBasicAttack.h"
#include "Core/Timer/Timer.h"
#include "Core/Game/Component/RenderComponent/CmdRenderComponent.h"
#include "Core/Game/GameManager.h"
#include "Core/ObjectPool/ObjectPool.h"
#include "Core/Game/Composite/Unit/Unit.h"
#include "Core/Game/Composite/Missile/Missile.h"
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

    auto missile = ObjectPool<Missile>::GetWithInit();
    auto render = missile->GetComponent<CmdRenderComponent>();
    if (render == nullptr)
        return;

    render->SetShape(L'o', Color::BLUE);
    missile->SetDamage(20);
    missile->SetMaxHp(1);
    missile->InitHp();
    missile->SetAttackMask(owner->GetAttackMask());
    missile->SetHitMask(owner->GetHitMask());
    missile->SetPos(owner->GetPos());
    missile->SetSpeed(80.0f);
    missile->SetMovePowerFrict(0.0f);
    missile->AddMovePower(owner->GetDirection());
    GameManager::GetInstance().RegisterCollision(missile, owner->GetSection());
    GameManager::GetInstance().AddRender(missile);
}

void SkillBasicAttack::OnUsing(float dt)
{
}

void SkillBasicAttack::OnEndUse()
{
}
