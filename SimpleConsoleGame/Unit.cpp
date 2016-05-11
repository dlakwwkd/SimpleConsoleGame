#include "stdafx.h"
#include "Unit.h"
SCE_USE


Unit::Unit()
:   m_Pos{0.0f, 0.0f},
    m_MovePower{0.0f, 0.0f},
    m_MovePowerLimit(1.0f),
    m_MovePowerFrict(1.5f),
    m_Speed(50.0f)
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
    m_MovePower -= m_MovePower * (m_MovePowerFrict * dt); // 마찰로 인한 속력 저하
    MovePowerFixInLimit();

    float speed = m_Speed * dt;
    m_Pos.m_X += m_MovePower.m_X * (speed * 2.0f);
    m_Pos.m_Y += m_MovePower.m_Y * speed;
    SyncCoordFromPos();
}

void Unit::Render() const noexcept
{
    Object::Render();
}
