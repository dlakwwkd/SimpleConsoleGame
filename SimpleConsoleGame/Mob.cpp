#include "stdafx.h"
#include "Mob.h"
#include "Dummy.h"
#include "Core/Console/Shape.hpp"
SCE_USE


Mob::Mob()
{
    Init();
}


Mob::~Mob()
{
    Release();
}

void Mob::Init()
{
    Unit::Init();
    SetShape(Shape(L'●', Color::YELLOW));
    SetDepth(1);
    m_ToPosShow = std::make_unique<Dummy>();
    m_ToPosShow->SetShape(Shape(L'＋', Color::RED));
    m_ToPosShow->SetShow(false);
    m_ToPosShow->SetDepth(0);
}

void Mob::Release()
{
    m_ToPosShow.reset();
    Unit::Release();
}

void Mob::Update(float dt)
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

void Mob::Render()
{
    m_ToPosShow->Render();
    Object::Render();
}



void Mob::AI(float dt)
{
    int randNum = static_cast<int>(1.0f / dt);
    randNum = std::max<int>(3, randNum);
    if (rand() % randNum == 0)
    {
        static auto& console = Console::GetInstance();
        auto toX = static_cast<float>(rand() % console.GetScreenWidth() / 2);
        auto toY = static_cast<float>(rand() % console.GetScreenHeight() - 1);
        m_ToPos.Set(toX, toY);
        m_ToPosShow->SetCoord(static_cast<short>(m_ToPos.m_X * 2.0f), static_cast<short>(m_ToPos.m_Y));
        m_ToPosShow->SetShow(false);

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
