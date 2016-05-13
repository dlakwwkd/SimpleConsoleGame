#include "stdafx.h"
#include "Unit.h"
#include "Core/Console/Console.h"
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
    SyncCoordFromPos();
}

void Unit::Render()
{
    Object::Render();
}



void Unit::PosFixInScreanBoundary() noexcept
{
    auto bound = Vec2(Console::GetInstance().GetScreenSize());
    bound.m_X -= 1.0f;
    bound.m_Y -= 2.0f;

    if (m_Pos.m_X < 0.0f)
    {
        m_Pos.m_X = 0.0f;
        m_MovePower.m_X = 0.0f;
    }
    else if (m_Pos.m_X > bound.m_X)
    {
        m_Pos.m_X = bound.m_X;
        m_MovePower.m_X = 0.0f;
    }

    if (m_Pos.m_Y < 0.0f)
    {
        m_Pos.m_Y = 0.0f;
        m_MovePower.m_Y = 0.0f;
    }
    else if (m_Pos.m_Y > bound.m_Y)
    {
        m_Pos.m_Y = bound.m_Y;
        m_MovePower.m_Y = 0.0f;
    }
}