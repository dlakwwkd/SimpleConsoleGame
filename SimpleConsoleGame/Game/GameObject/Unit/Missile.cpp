﻿#include "stdafx.h"
#include "Missile.h"
//----------------------------------------------------------------------------------------------------
#include "SimpleConsoleEngine/Core/Console/Shape.hpp"
#include "SimpleConsoleEngine/Core/Timer/Timer.h"
//----------------------------------------------------------------------------------------------------
#include "../Dummy.h"
SCE_USE


Missile::Missile()
:   m_ToPos{ 0.0f, 0.0f },
    m_ToPosChangeProbability(0.2f)
{
    Init();
}


Missile::~Missile()
{
    Release();
}

void Missile::Init()
{
    Unit::Init();
    SetShape(Shape(L'●', Color::YELLOW));
    SetDepth(3);
    m_ToPosShow = std::make_shared<Dummy>();
    m_ToPosShow->SetShape(Shape(L'✘', Color::MAGENTA));
    m_ToPosShow->SetShow(false);
    m_ToPosShow->SetDepth(1);
    m_AITimer = std::make_shared<Timer>(1.0f);
}

void Missile::Release()
{
    m_AITimer.reset();
    m_ToPosShow.reset();
    Unit::Release();
}

void Missile::Update(float dt)
{
    Vec2 displacement = m_ToPos - m_Pos;
    float distance = displacement.Length();
    if (distance < 1.0f)
    {
        m_MovePower.SetZero();
        m_ToPosShow->SetShow(false);
    }
    else
    {
        float maxMoveDist = m_Speed / m_MovePowerFrict;
        if (distance > maxMoveDist)
        {
            m_MovePower = displacement * (m_MovePowerLimit / distance);
        }
    }
    Unit::Update(dt);
}

void Missile::Render()
{
    m_ToPosShow->Render();
    Unit::Render();
}



void Missile::AI(float dt)
{
    m_AITimer->AccumDt(dt);
    if (!m_AITimer->DurationCheck())
    {
        return;
    }
    int randRange = static_cast<int>(1.0f / m_ToPosChangeProbability);
    if (rand() % randRange == 0)
    {
        static auto& console = Console::GetInstance();
        auto toX = static_cast<float>(rand() % console.GetScreenWidth() / 2);
        auto toY = static_cast<float>(rand() % console.GetScreenHeight() - 1);
        m_ToPos.Set(toX, toY);
        m_ToPosShow->SetCoord(static_cast<short>(m_ToPos.m_X * 2.0f), static_cast<short>(m_ToPos.m_Y));
        m_ToPosShow->SetShow(true);

        Vec2 displacement = m_ToPos - m_Pos;
        float distance = displacement.Length();
        if (distance < 1.0f)
        {
            m_MovePower.SetZero();
            m_ToPosShow->SetShow(false);
        }
        else
        {
            float maxMoveDist = m_Speed / m_MovePowerFrict;
            if (distance > maxMoveDist)
            {
                m_MovePower = displacement * (m_MovePowerLimit / distance);
            }
            else
            {
                m_MovePower = displacement * (m_MovePowerLimit / maxMoveDist);
            }
        }
    }
}

void Missile::SetAIRatio(float ratio)
{
    if (m_AITimer)
    {
        m_AITimer->SetDuration(ratio);
    }
}
