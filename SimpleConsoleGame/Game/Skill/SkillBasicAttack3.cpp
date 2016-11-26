#include "stdafx.h"
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
    auto render = missile->GetComponent<CmdRenderComponent>();
    if (render == nullptr)
        return;

    auto collision = missile->GetComponent<CollisionComponent>();
    if (collision == nullptr)
        return;

    render->SetShape(L'x');
    render->SetColor(Color::MAGENTA);
    collision->SetDamage(10);
    collision->SetMaxHp(1);
    collision->InitHp();
    collision->SetAttackMask(owner->GetComponent<CollisionComponent>()->GetAttackMask());
    collision->SetHitMask(owner->GetComponent<CollisionComponent>()->GetHitMask());
    missile->SetPos(owner->GetPos());
    missile->SetSpeed(100.0f);
    missile->SetMovePowerFrict(0.0f);
    missile->AddMovePower(owner->GetDirection());
    GameManager::GetInstance().RegisterCollision(missile, owner->GetComponent<CollisionComponent>()->GetSection());
    GameManager::GetInstance().AddRender(missile);
}

void SkillBasicAttack3::OnUsing(float _dt)
{
}

void SkillBasicAttack3::OnEndUse()
{
}
