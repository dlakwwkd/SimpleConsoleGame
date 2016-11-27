﻿#include "stdafx.h"
#include "SkillBasicAttack3.h"
#include "Core/Math/Vec2.h"
#include "Core/Game/Component/RenderComponent/CmdRenderComponent.h"
#include "Core/Game/Component/CollisionComponent/CollisionComponent.h"
#include "Core/Game/Composite/Unit/Missile/Missile.h"
#include "Core/Game/GameManager.h"
SCE_USE


SkillBasicAttack3::SkillBasicAttack3()
{
    SetDuration(State::COOLTIME, 0.01f);
}


void SkillBasicAttack3::OnPrepare(float _dt)
{
}

void SkillBasicAttack3::OnBeginUse()
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

    render->SetShape(L'x');
    render->SetColor(Color::MAGENTA);
    collision->SetDamage(10);
    collision->SetMaxHp(1);
    collision->InitHp();
    collision->SetAttackMask(ownerCollision->GetAttackMask());
    collision->SetHitMask(ownerCollision->GetHitMask());
    missile->SetPos(owner->GetPos());
    missile->SetSpeed(100.0f);
    missile->SetMovePowerFrict(0.0f);
    missile->AddMovePower(owner->GetDirection());

    static auto& gm = GameManager::GetInstance();
    gm.RegisterCollision(missile, ownerCollision->GetSection());
    gm.AddRender(missile);
}

void SkillBasicAttack3::OnUsing(float _dt)
{
}

void SkillBasicAttack3::OnEndUse()
{
}