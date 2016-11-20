#include "stdafx.h"
#include "Hero.h"
//----------------------------------------------------------------------------------------------------
#include "Core/Timer/Timer.h"
#include "Core/Console/Console.h"
#include "Core/Game/Component/RenderComponent/CmdRenderComponent.h"
#include "Core/Game/GameManager.h"
#include "Core/ObjectPool/ObjectPool.h"
#include "Core/Game/Composite/Effect/Dummy.h"
#include "Core/Game/Skill.h"
//----------------------------------------------------------------------------------------------------
#include "../../Skill/SkillBasicAttack.h"
#include "../../Skill/SkillBasicAttack2.h"
#include "../../Skill/SkillBasicAttack3.h"
#include "../../Skill/SkillBasicAttackSwap.h"
SCE_USE


Hero::Hero() noexcept
{
    Init();
}


Hero::~Hero()
{
    Release();
}

void Hero::Init()
{
    auto render = GetComponent<CmdRenderComponent>();
    if (render == nullptr)
        return;

    render->SetShape(L'▣', Color::GREEN);
    render->SetDepth(5);

    SetMovePowerLimit(0.25f);
    SetMovePowerFrict(4.0f);
    SetSpeed(50.0f);
    SetMaxHp(500);
    InitHp();
    SetDamage(10);
    SetHitMask(CollisionMask::PLAYER);
    SetAttackMask(CollisionMask::ENEMY);

    auto screenSize = Console::GetInstance().GetScreenSize();
    SetPos(Coord::ConvertToVec2(screenSize) / 2);
}

void Hero::Release()
{
}

void Hero::Update(float dt)
{
    Unit::Update(dt);
}

void Hero::Render()
{
    Unit::Render();
}



void Hero::SetDefaultAttack()
{
    m_DefaultAttack = ObjectPool<SkillBasicAttack>::Get();
    AddSkill(m_DefaultAttack);
    AddSkill(ObjectPool<SkillBasicAttack2>::Get());
    AddSkill(ObjectPool<SkillBasicAttack3>::Get());

    m_MissileSwap = ObjectPool<SkillBasicAttackSwap>::Get();
    AddSkill(m_MissileSwap);
}

void Hero::ShootMissile()
{
    if (m_DefaultAttack == nullptr)
        return;

    m_DefaultAttack->UseSkill();
}

void Hero::SwapMissile()
{
    if (m_MissileSwap == nullptr)
        return;

    m_MissileSwap->UseSkill();
}

void Hero::SwapMissile(int idx)
{
    if (idx < 0 || idx >= m_SkillList.size())
        return;

    m_DefaultAttack = m_SkillList.at(idx);
}
