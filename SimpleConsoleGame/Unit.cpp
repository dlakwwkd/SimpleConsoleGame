#include "stdafx.h"
#include "Unit.h"
#include "Core/Console/Console.h"
SCE_USE


Unit::Unit()
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
    SyncCoordFromPos();
}

void Unit::Render()
{
    Object::Render();
}



void Unit::PosFixInScreanBoundary() noexcept
{
    auto xBound = static_cast<float>(DEF_CONSOLE_SIZE.m_X / 2 - 2);
    auto yBound = static_cast<float>(DEF_CONSOLE_SIZE.m_Y - 1);

    if (m_Pos.m_X < 0)
    {
        m_Pos.m_X = 0.0f;
        m_MovePower.m_X = 0.0f;
    }
    else if (m_Pos.m_X > xBound)
    {
        m_Pos.m_X = xBound;
        m_MovePower.m_X = 0.0f;
    }
    if (m_Pos.m_Y < 0)
    {
        m_Pos.m_Y = 0.0f;
        m_MovePower.m_Y = 0.0f;
    }
    else if (m_Pos.m_Y > yBound)
    {
        m_Pos.m_Y = yBound;
        m_MovePower.m_Y = 0.0f;
    }
}