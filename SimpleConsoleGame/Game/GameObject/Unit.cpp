#include "stdafx.h"
#include "Unit.h"
//----------------------------------------------------------------------------------------------------
#include "Core/Console/Console.h"
#include "Core/Game/Component/RenderComponent/CmdRenderComponent.h"
#include "Core/Game/GameManager.h"
//----------------------------------------------------------------------------------------------------
#include "Dummy.h"
#include "../Game.h"
#include "../Section.h"
#include "../Skill.h"
SCE_USE


bool Unit::IsCollisionAble(const UnitPtr& unitA, const UnitPtr& unitB)
{
    if (unitA == nullptr || unitB == nullptr)
        return false;

    // 둘다 서로 공격할 수 없는 유닛이라면, 충돌체크를 건너뛰도록
    return unitA->m_HitMask & unitB->m_AttackMask
        || unitB->m_HitMask & unitA->m_AttackMask;
}



Unit::Unit()
:   m_Pos{0.0f, 0.0f},
    m_Direction(Vec2::UP),
    m_MovePower{0.0f, 0.0f},
    m_MovePowerLimit(1.0f),
    m_MovePowerFrict(1.5f),
    m_Speed(100.0f),
    m_MaxHp(0),
    m_CurHp(0),
    m_Damage(0),
    m_IsDeath(false),
    m_HitLock(false),
    m_HitRenderFlag(false),
    m_HitMask(CollisionMask::NONE),
    m_AttackMask(CollisionMask::NONE)
{
    AddComponent<CmdRenderComponent>();
}


Unit::~Unit()
{
}

void Unit::Update(float dt)
{
    if (m_IsDeath)
        return;

    MovePowerFixInLimit();
    m_Pos += m_MovePower * (m_Speed / m_MovePowerLimit * dt);   // 현재 속도만큼 이동
    m_MovePower -= m_MovePower * (m_MovePowerFrict * dt);       // 마찰로 인한 속력 저하
    PosFixInScreanBoundary();

    for (auto& skill : m_SkillList)
    {
        skill->Update(dt);
    }
}

void Unit::Render()
{
    if (m_IsDeath)
        return;

    auto render = GetComponent<CmdRenderComponent>();
    if (render == nullptr)
        return;

    render->SetCoord(Coord(m_Pos));
    //DirectionShow();

    if (m_HitRenderFlag)
    {
        m_HitRenderFlag = false;
        auto orgBGColor = render->GetBGColor();
        render->SetBGColor(Color::MAGENTA);
        GameObject::Render();
        render->SetBGColor(orgBGColor);
    }
    else
    {
        GameObject::Render();
    }
}



void Unit::Hitted(int damage)
{
    if (m_IsDeath || m_HitLock)
        return;

    m_HitLock = true;
    GameManager::GetInstance().CallFuncAfterP(0.2f,
        std::dynamic_pointer_cast<Unit>(shared_from_this()),
        &Unit::SetHitLock,
        false);

    m_HitRenderFlag = true;
    m_CurHp -= damage;
    if (m_CurHp <= 0)
    {
        m_CurHp = 0;
        Death();
    }
}

void Unit::Death()
{
    if (m_IsDeath)
        return;

    m_IsDeath = true;
    auto corpse = std::make_shared<Dummy>();
    auto render = corpse->GetComponent<CmdRenderComponent>();
    if (render != nullptr)
    {
        render->SetCoord(Coord(m_Pos));
        render->SetShape(GetComponent<CmdRenderComponent>()->GetShape());
        render->SetColor(Color::BLACK);
        render->SetBGColor(Color::RED);
        GameManager::GetInstance().GetGame<Game>().AddOnlyRender(corpse, 1.f);
    }
}



bool Unit::IsDeath() const
{
    return m_IsDeath;
}

bool Unit::CanAttack(const UnitPtr& target) const
{
    if (target == nullptr)
        return false;

    return (target->m_HitMask & m_AttackMask) == 0 ? false : true;
}



void Unit::InitHp()
{
    m_CurHp = m_MaxHp;
}

void Unit::SetMaxHp(int maxHp)
{
    if (maxHp > 0)
    {
        m_MaxHp = maxHp;
    }
}

void Unit::SetDamage(int damage)
{
    m_Damage = damage;
}

void Unit::SetSpeed(float speed)
{
    m_Speed = speed;
}

void Unit::SetMovePowerLimit(float ratio)
{
    m_MovePowerLimit = ratio;
}

void Unit::SetMovePowerFrict(float ratio)
{
    m_MovePowerFrict = ratio;
}

void Unit::SetPos(const Vec2& pos)
{
    m_Pos = pos;
}

void Unit::SetSection(const SectionPtr& section)
{
    m_Section = section;
}

void Unit::SetHitMask(CollisionMask mask)
{
    m_HitMask = mask;
}

void Unit::SetAttackMask(CollisionMask mask)
{
    m_AttackMask = mask;
}

void Unit::AddMovePower(const Vec2& addPower)
{
    m_MovePower += addPower;
    m_Direction = m_MovePower.GetNormalized();
}

void Unit::AddSkill(const SkillPtr& skill)
{
    if (skill == nullptr)
        return;

    skill->SetOwner(shared_from_this());
    m_SkillList.push_back(skill);
}



int Unit::GetDamage() const
{
    return m_Damage;
}

Vec2 Unit::GetPos() const
{
    return m_Pos;
}

Vec2 Unit::GetDirection() const
{
    return m_Direction;
}

Unit::SectionPtr Unit::GetSection() const
{
    return m_Section.lock();
}

Unit::CollisionMask Unit::GetHitMask() const
{
    return m_HitMask;
}

Unit::CollisionMask Unit::GetAttackMask() const
{
    return m_AttackMask;
}



void Unit::MovePowerFixInLimit()
{
    float length = m_MovePower.Length();
    if (length < 0.0001f)
    {
        m_MovePower.SetZero();
    }
    else if (length > m_MovePowerLimit)
    {
        m_MovePower *= m_MovePowerLimit / length;
    }
}

void Unit::PosFixInScreanBoundary()
{
    static auto& console = Console::GetInstance();
    Vec2 bound(Coord::ConvertToVec2(console.GetScreenSize()));

    if (m_Pos.GetX() < 0.0f)
    {
        m_Pos.SetX(0.0f);
        m_MovePower.SetX(0.0f);
    }
    else if (m_Pos.GetX() > bound.GetX())
    {
        m_Pos.SetX(bound.GetX());
        m_MovePower.SetX(0.0f);
    }

    if (m_Pos.GetY() < 0.0f)
    {
        m_Pos.SetY(0.0f);
        m_MovePower.SetY(0.0f);
    }
    else if (m_Pos.GetY() > bound.GetY())
    {
        m_Pos.SetY(bound.GetY());
        m_MovePower.SetY(0.0f);
    }
}

void Unit::DirectionShow() const
{
    if (m_MovePowerFrict < 0.01f || m_MovePowerLimit < 0.01f)
        return;

    float power = m_MovePower.Length();
    Vec2 dir = m_MovePower / power;
    Vec2 temp = m_Pos;

    static Dummy dummy;
    auto length = static_cast<size_t>(power * m_Speed / m_MovePowerFrict / m_MovePowerLimit);
    for (size_t i = 0; i < length; ++i)
    {
        temp += dir;
        dummy.SetPos(temp);
        dummy.Render();
    }
}

void Unit::SetHitLock(bool lock)
{
    m_HitLock = lock;
}
