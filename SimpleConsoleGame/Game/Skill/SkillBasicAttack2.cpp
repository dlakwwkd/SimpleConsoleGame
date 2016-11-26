#include "stdafx.h"
#include "SkillBasicAttack2.h"
#include "Core/Math/Vec2.h"
#include "Core/Game/Component/RenderComponent/CmdRenderComponent.h"
#include "Core/Game/Component/CollisionComponent/CollisionComponent.h"
#include "Core/Game/Composite/Unit/Missile/Missile.h"
#include "Core/Game/GameManager.h"
SCE_USE


SkillBasicAttack2::SkillBasicAttack2()
{
    SetDuration(State::COOLTIME, 0.3f);
}


void SkillBasicAttack2::OnPrepare(float _dt)
{
}

void SkillBasicAttack2::OnBeginUse()
{
    auto owner = GetOwner<Unit>();
    if (owner == nullptr)
        return;

    auto missile = ObjectPool<Missile>::GetWithInit();
    auto render = missile->GetComponent<CmdRenderComponent>();
    if (render == nullptr)
        return;

    auto collision = missile->GetComponent<CollisionComponent>();
    if (collision == nullptr)
        return;

    render->SetShape(L'●');
    render->SetColor(Color::WHITE);
    collision->SetDamage(60);
    collision->SetMaxHp(20);
    collision->InitHp();
    collision->SetAttackMask(owner->GetComponent<CollisionComponent>()->GetAttackMask());
    collision->SetHitMask(owner->GetComponent<CollisionComponent>()->GetHitMask());
    missile->SetPos(owner->GetPos());
    missile->SetSpeed(50.f);
    missile->SetMovePowerFrict(1.5f);
    missile->AddMovePower(owner->GetDirection());

    static auto& gm = GameManager::GetInstance();
    gm.RegisterCollision(missile, owner->GetComponent<CollisionComponent>()->GetSection());
    gm.AddRender(missile);
    gm.CallFuncAfterP(2.f, missile, &Missile::Death);
}

void SkillBasicAttack2::OnUsing(float _dt)
{
}

void SkillBasicAttack2::OnEndUse()
{
}
