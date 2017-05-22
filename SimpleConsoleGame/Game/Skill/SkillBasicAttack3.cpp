#include "stdafx.h"
#include "SkillBasicAttack3.h"
#include "Core/Math/Vec2.h"
#include "Core/Game/Component/RenderComponent/CmdRenderComponent.h"
#include "Core/Game/Component/CollisionComponent/CollisionComponent.h"
#include "Core/Game/Composite/Unit/Missile/Missile.h"
#include "Core/Game/GameManager.h"
#include "Core/Game/EffectManager.h"
#include "Core/Console/Color.hpp"
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

    missile->SetPos(owner->GetPos());
    missile->SetSpeed(100.0f);
    missile->SetMovePowerFrict(0.0f);
    missile->AddMovePower(owner->GetDirection());
    missile->SetDeathEffect(EffectType::EXPLOSION_C);

    if (auto& render = missile->GetRender())
    {
        render->SetShape(L'x');
        render->SetColor(Color::MAGENTA);
    }

    if (auto& collision = missile->GetCollision())
    {
        collision->SetDamage(10);
        collision->SetMaxHp(1);
        collision->InitHp();

        if (auto& ownerCollision = owner->GetCollision())
        {
            collision->SetAttackMask(ownerCollision->GetAttackMask());
            collision->SetHitMask(ownerCollision->GetHitMask());

            static auto& gm = GameManager::GetInstance();
            gm.RegisterCollision(missile, ownerCollision->GetSection());
            gm.AddRender(missile);
            gm.CallFuncAfterP(5.f, missile, &Missile::Death);
        }
    }
}

void SkillBasicAttack3::OnUsing(float _dt)
{
}

void SkillBasicAttack3::OnEndUse()
{
}
