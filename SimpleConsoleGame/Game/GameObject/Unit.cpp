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
SCE_USE


Unit::Unit()
:   m_Pos{0.0f, 0.0f},
    m_MovePower{0.0f, 0.0f},
    m_MovePowerLimit(1.0f),
    m_MovePowerFrict(1.5f),
    m_Speed(100.0f),
    m_MaxHp(0),
    m_CurHp(0),
    m_IsDeath(false),
    m_HitRenderFlag(false)
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
}

void Unit::Render()
{
    if (m_IsDeath)
        return;

    auto render = GetComponent<CmdRenderComponent>();
    if (render == nullptr)
        return;

    render->SetCoord(Coord(m_Pos));
    DirectionShow();

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
    if (m_IsDeath)
        return;

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

void Unit::SetSpeed(float speed)
{
    m_Speed = speed;
}

void Unit::SetSection(const SectionPtr& section)
{
    m_Section = section;
}

void Unit::AddMovePower(const Vec2& addPower)
{
    m_MovePower += addPower;
}



Vec2 Unit::GetPos() const
{
    return m_Pos;
}

Unit::SectionPtr Unit::GetSection() const
{
    return m_Section;
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
