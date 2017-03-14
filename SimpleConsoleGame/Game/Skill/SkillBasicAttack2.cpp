#include "stdafx.h"
#include "SkillBasicAttack2.h"
#include "Core/Math/Vec2.h"
#include "Core/Game/Component/RenderComponent/CmdRenderComponent.h"
#include "Core/Game/Component/CollisionComponent/CollisionComponent.h"
#include "Core/Game/Composite/Unit/Missile/Missile.h"
#include "Core/Game/GameManager.h"
#include "Core/Game/EffectManager.h"
#include "Core/Console/Color.hpp"
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

    missile->SetPos(owner->GetPos());
    missile->SetSpeed(50.f);
    missile->SetMovePowerFrict(1.5f);
    missile->AddMovePower(owner->GetDirection());
    missile->SetDeathEffect(EffectType::EXPLOSION_B);

    if (auto& render = missile->GetRender())
    {
        render->SetShape(L'●');
        render->SetColor(Color::WHITE);
    }

    if (auto& collision = missile->GetCollision())
    {
        collision->SetDamage(60);
        collision->SetMaxHp(20);
        collision->InitHp();

        if (auto& ownerCollision = owner->GetCollision())
        {
            collision->SetAttackMask(ownerCollision->GetAttackMask());
            collision->SetHitMask(ownerCollision->GetHitMask());

            static auto& gm = GameManager::GetInstance();
            gm.RegisterCollision(missile, ownerCollision->GetSection());
            gm.AddRender(missile);
            gm.CallFuncAfterP(2.f, missile, &Missile::Death);
        }
    }
}

void SkillBasicAttack2::OnUsing(float _dt)
{
}

void SkillBasicAttack2::OnEndUse()
{
}
