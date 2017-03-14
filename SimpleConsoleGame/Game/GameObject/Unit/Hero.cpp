#include "stdafx.h"
#include "Hero.h"
#include "Core/Math/Vec2.h"
#include "Core/Timer/Timer.h"
#include "Core/Console/Console.h"
#include "Core/Console/Coord.h"
#include "Core/Console/Color.hpp"
#include "Core/Game/Component/RenderComponent/CmdRenderComponent.h"
#include "Core/Game/Component/CollisionComponent/CollisionComponent.h"
#include "../../Skill/SkillBasicAttack.h"
#include "../../Skill/SkillBasicAttack2.h"
#include "../../Skill/SkillBasicAttack3.h"
#include "../../Skill/SkillBasicAttackSwap.h"
SCE_USE


struct Hero::impl
{
    impl() noexcept
        : defaultAttack{}
        , missileSwap{}
    {
    }
    
    std::shared_ptr<Skill> defaultAttack;
    std::shared_ptr<Skill> missileSwap;
};


Hero::Hero() noexcept
    : pimpl{ std::make_unique<impl>() }
{
}

Hero::~Hero()
{
}


void Hero::Init()
{
    Unit::Init();
    if (auto& render = GetRender())
    {
        render->SetShape(L'▣');
        render->SetColor(Color::GREEN);
        render->SetDepth(5);
    }
    if (auto& collision = GetCollision())
    {
        collision->SetMaxHp(500);
        collision->InitHp();
        collision->SetDamage(10);
        collision->SetHitMask(CollisionComponent::CollisionMask::PLAYER);
        collision->SetAttackMask(CollisionComponent::CollisionMask::ENEMY);
    }
    SetMovePowerLimit(0.25f);
    SetMovePowerFrict(4.0f);
    SetSpeed(50.0f);

    auto screenSize = Console::GetInstance().GetScreenSize();
    SetPos(Coord::ConvertToVec2(screenSize) / 2);
}

void Hero::Release()
{
    Unit::Release();
}

void Hero::Update(float _dt)
{
    Unit::Update(_dt);
}

void Hero::Render()
{
    Unit::Render();
}



void Hero::SetDefaultAttack()
{
    pimpl->defaultAttack = ObjectPool<SkillBasicAttack>::Get();
    AddSkill(pimpl->defaultAttack);
    AddSkill(ObjectPool<SkillBasicAttack2>::Get());
    AddSkill(ObjectPool<SkillBasicAttack3>::Get());

    pimpl->missileSwap = ObjectPool<SkillBasicAttackSwap>::Get();
    AddSkill(pimpl->missileSwap);
}

void Hero::ShootMissile()
{
    if (pimpl->defaultAttack == nullptr)
        return;

    pimpl->defaultAttack->UseSkill();
}

void Hero::SwapMissile()
{
    if (pimpl->missileSwap == nullptr)
        return;

    pimpl->missileSwap->UseSkill();
}

void Hero::SwapMissile(int _idx)
{
    if (_idx < 0 || _idx >= GetSkillList().size())
        return;

    pimpl->defaultAttack = GetSkillList().at(_idx);
}
