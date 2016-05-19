#include "stdafx.h"
#include "Unit.h"
//----------------------------------------------------------------------------------------------------
#include "SimpleConsoleEngine/Core/Console/Console.h"
//----------------------------------------------------------------------------------------------------
#include "Object/Dummy.h"
SCE_USE


Unit::Unit() noexcept
:   m_Pos{0.0f, 0.0f},
    m_MovePower{0.0f, 0.0f},
    m_MovePowerLimit(1.0f),
    m_MovePowerFrict(1.5f),
    m_Speed(100.0f)
{
}


Unit::~Unit()
{
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
    SetCoord(m_Pos);
}

void Unit::Render()
{
    float power = m_MovePower.Length();
    Vec2 dir = m_MovePower / power;
    Vec2 temp = m_Pos;

    Dummy dummy;
    dummy.SetShape(Shape(L'+', Color::MAGENTA));
    auto length = static_cast<size_t>(power * m_Speed / m_MovePowerFrict);
    for (size_t i = 0; i < length; ++i)
    {
        temp += dir;
        dummy.SetCoord(temp);
        dummy.Render();
    }

    Object::Render();
}
