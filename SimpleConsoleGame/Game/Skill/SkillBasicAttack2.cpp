#include "stdafx.h"
#include "SkillBasicAttack2.h"
#include "Core/Math/Vec2.h"
#include "Core/Game/Component/RenderComponent/CmdRenderComponent.h"
#include "Core/Game/Component/CollisionComponent/CollisionComponent.h"
#include "Core/Game/Composite/Unit/Missile/Missile.h"
#include "Core/Game/GameManager.h"
#include "Core/Game/EffectManager.h"
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
    if (missile == nullptr)
        return;

    auto render = missile->IRenderObject::Get<CmdRenderComponent>();
    if (render == nullptr)
        return;

    auto collision = missile->ICollisionObject::Get<CollisionComponent>();
    if (collision == nullptr)
        return;

    auto ownerCollision = owner->ICollisionObject::Get<CollisionComponent>();
    if (ownerCollision == nullptr)
        return;

    render->SetShape(L'●');
    render->SetColor(Color::WHITE);
    collision->SetDamage(60);
    collision->SetMaxHp(20);
    collision->InitHp();
    collision->SetAttackMask(ownerCollision->GetAttackMask());
    collision->SetHitMask(ownerCollision->GetHitMask());
    missile->SetPos(owner->GetPos());
    missile->SetSpeed(50.f);
    missile->SetMovePowerFrict(1.5f);
    missile->AddMovePower(owner->GetDirection());
    missile->SetExplosionEffect(EffectType::EXPLOSION_B);

    static auto& gm = GameManager::GetInstance();
    gm.RegisterCollision(missile, ownerCollision->GetSection());
    gm.AddRender(missile);
    gm.CallFuncAfterP(2.f, missile, &Missile::Death);
}

void SkillBasicAttack2::OnUsing(float _dt)
{
}

void SkillBasicAttack2::OnEndUse()
{
}
