﻿#include "stdafx.h"
#include "Unit.h"
//----------------------------------------------------------------------------------------------------
#include "SimpleConsoleEngine/Core/Console/Console.h"
#include "SimpleConsoleEngine/Core/Game/Component/CmdRenderComponent.h"
//----------------------------------------------------------------------------------------------------
#include "Dummy.h"
SCE_USE


Unit::Unit() noexcept
:   m_Pos{0.0f, 0.0f},
    m_MovePower{0.0f, 0.0f},
    m_MovePowerLimit(1.0f),
    m_MovePowerFrict(1.5f),
    m_Speed(100.0f)
{
    auto render = IComponent::Create<CmdRenderComponent>();
    InsertComponent<CmdRenderComponent>(render);
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
    auto render = GetComponent<CmdRenderComponent>();
    if (render != nullptr)
    {
        render->SetCoord(Coord(m_Pos));
    }
}

void Unit::Render()
{
    float power = m_MovePower.Length();
    Vec2 dir = m_MovePower / power;
    Vec2 temp = m_Pos;

    Dummy dummy;
    auto render = dummy.GetComponent<CmdRenderComponent>();
    if (render != nullptr)
    {
        render->SetShape(Shape(L'+', Color::BLUE));
        auto length = static_cast<size_t>(power * m_Speed / m_MovePowerFrict / m_MovePowerLimit);
        for (size_t i = 0; i < length; ++i)
        {
            temp += dir;
            render->SetCoord(Coord(temp));
            dummy.Render();
        }

    }
    GameObject::Render();
}
