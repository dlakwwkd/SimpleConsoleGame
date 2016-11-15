#include "stdafx.h"
#include "Hero.h"
//----------------------------------------------------------------------------------------------------
#include "Core/Timer/Timer.h"
#include "Core/Console/Console.h"
#include "Core/Game/Component/RenderComponent/CmdRenderComponent.h"
#include "Core/Game/GameManager.h"
//----------------------------------------------------------------------------------------------------
#include "../Dummy.h"
#include "../../Skill.h"
#include "../../Skill/SkillBasicAttack.h"
#include "../../Skill/SkillBasicAttack2.h"
#include "../../Skill/SkillBasicAttack3.h"
#include "../../Skill/SkillBasicAttackSwap.h"
SCE_USE


Hero::Hero()
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

    render->SetShape(Shape(L'▣', Color::GREEN));
    render->SetDepth(5);

    m_MovePowerLimit = 0.25f;
    m_MovePowerFrict = 4.0f;
    m_Speed = 50.0f;
    m_CurHp = m_MaxHp = 500;
    m_Damage = 10;
    m_HitMask = CollisionMask::PLAYER;
    m_AttackMask = CollisionMask::ENEMY;

    auto screenSize = Console::GetInstance().GetScreenSize();
    m_Pos = Coord::ConvertToVec2(screenSize) / 2;
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
    m_DefaultAttack = std::make_shared<SkillBasicAttack>();
    AddSkill(m_DefaultAttack);
    AddSkill(std::make_shared<SkillBasicAttack2>());
    AddSkill(std::make_shared<SkillBasicAttack3>());

    m_MissileSwap = std::make_shared<SkillBasicAttackSwap>();
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
