#include "stdafx.h"
#include "Unit.h"
//----------------------------------------------------------------------------------------------------
#include "Core/Console/Console.h"
#include "Core/Game/Component/RenderComponent/CmdRenderComponent.h"
//----------------------------------------------------------------------------------------------------
#include "Dummy.h"
SCE_USE


Unit::Unit()
:   m_Pos{0.0f, 0.0f},
    m_MovePower{0.0f, 0.0f},
    m_MovePowerLimit(1.0f),
    m_MovePowerFrict(1.5f),
    m_Speed(100.0f)
{
    AddComponent<CmdRenderComponent>();
}


Unit::~Unit()
{
    Release();
}

void Unit::Init()
{
}

void Unit::Release()
{
}

void Unit::Update(float dt)
{
    MovePowerFixInLimit();
    m_Pos += m_MovePower * (m_Speed / m_MovePowerLimit * dt);   // 현재 속도만큼 이동
    m_MovePower -= m_MovePower * (m_MovePowerFrict * dt);       // 마찰로 인한 속력 저하
    PosFixInScreanBoundary();
}

void Unit::Render()
{
    auto render = GetComponent<CmdRenderComponent>();
    if (render == nullptr)
        return;

    render->SetCoord(Coord(m_Pos));
    DirectionShow();
    GameObject::Render();
}



void Unit::SetSpeed(float speed)
{
    m_Speed = speed;
}

void Unit::AddMovePower(const SCE::Vec2& addPower)
{
    m_MovePower += addPower;
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
    static auto& console = SCE::Console::GetInstance();
    SCE::Vec2 bound(SCE::Coord::ConvertToVec2(console.GetScreenSize()));

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

    Dummy dummy;
    auto render = dummy.GetComponent<CmdRenderComponent>();
    if (render == nullptr)
        return;

    render->SetShape(Shape(L'+', Color::BLUE));
    auto length = static_cast<size_t>(power * m_Speed / m_MovePowerFrict / m_MovePowerLimit);
    for (size_t i = 0; i < length; ++i)
    {
        temp += dir;
        render->SetCoord(Coord(temp));
        dummy.Render();
    }
}
