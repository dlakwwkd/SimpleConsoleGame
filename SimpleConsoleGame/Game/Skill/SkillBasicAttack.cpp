#include "stdafx.h"
#include "SkillBasicAttack.h"
#include "Core/Math/Vec2.h"
#include "Core/Game/Component/RenderComponent/CmdRenderComponent.h"
#include "Core/Game/Component/CollisionComponent/CollisionComponent.h"
#include "Core/Game/Composite/Unit/Missile/Missile.h"
#include "Core/Game/GameManager.h"
#include "Core/Game/EffectManager.h"
#include "Core/Console/Color.hpp"
SCE_USE


SkillBasicAttack::SkillBasicAttack()
{
    SetDuration(State::COOLTIME, 0.1f);
}


void SkillBasicAttack::OnPrepare(float _dt)
{
}

void SkillBasicAttack::OnBeginUse()
{
    auto owner = GetOwner<Unit>();
    if (owner == nullptr)
        return;

    auto missile = ObjectPool<Missile>::GetWithInit();
    if (missile == nullptr)
        return;

    missile->SetPos(owner->GetPos());
    missile->SetSpeed(80.0f);
    missile->SetMovePowerFrict(0.0f);
    missile->AddMovePower(owner->GetDirection());
    missile->SetDeathEffect(EffectType::EXPLOSION_A);

    if (auto& render = missile->GetRender())
    {
        render->SetShape(L'o');
        render->SetColor(Color::BLUE);
    }

    if (auto& collision = missile->GetCollision())
    {
        collision->SetDamage(20);
        collision->SetMaxHp(1);
        collision->InitHp();

        if (auto& ownerCollision = owner->GetCollision())
        {
            collision->SetAttackMask(ownerCollision->GetAttackMask());
            collision->SetHitMask(ownerCollision->GetHitMask());

            static auto& gm = GameManager::GetInstance();
            gm.RegisterCollision(missile, ownerCollision->GetSection());
            gm.AddRender(missile);
        }
    }
}

void SkillBasicAttack::OnUsing(float _dt)
{
}

void SkillBasicAttack::OnEndUse()
{
}
