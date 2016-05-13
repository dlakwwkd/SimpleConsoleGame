#include "stdafx.h"
#include "Mob.h"
#include "Dummy.h"
#include "Core/Console/Shape.hpp"
SCE_USE


Mob::Mob()
{
}


Mob::~Mob()
{
}

void Mob::Init()
{
    SetShape(Shape(L'●', Color::YELLOW));
    m_ToPosShow = std::make_unique<Dummy>();
    m_ToPosShow->SetShape(Shape(L'＋', Color::RED));
    m_ToPosShow->SetShow(false);
}

void Mob::Release()
{
    m_ToPosShow.reset();
    Unit::Release();
}

void Mob::Update(float dt)
{
    Vec2 displacement = m_ToPos - m_Pos;
    float length = displacement.Length();
    if (length < 1.0f)
    {
        m_MovePower = { 0.0f, 0.0f };
        m_ToPosShow->SetShow(false);
    }
    else
    {
        Vec2 dir = displacement / length;
        float maxMoveDist = m_Speed / m_MovePowerFrict;
        if (length > maxMoveDist)
        {
            m_MovePower = dir * m_MovePowerLimit;
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
        auto toX = static_cast<float>(rand() % DEF_CONSOLE_SIZE.m_X / 2 - 1);
        auto toY = static_cast<float>(rand() % DEF_CONSOLE_SIZE.m_Y);
        m_ToPos = Vec2(toX, toY);
        m_ToPosShow->SetCoord(Coord(static_cast<short>(m_ToPos.m_X * 2.0f), static_cast<short>(m_ToPos.m_Y)));
        m_ToPosShow->SetShow(true);

        Vec2 displacement = m_ToPos - m_Pos;
        float length = displacement.Length();
        if (length < 1.0f)
        {
            m_MovePower = { 0.0f, 0.0f };
        }
        else
        {
            Vec2 dir = displacement / length;
            float maxMoveDist = m_Speed / m_MovePowerFrict;
            if (length > maxMoveDist)
            {
                m_MovePower = dir * m_MovePowerLimit;
            }
            else
            {
                float distRatio = length / maxMoveDist;
                m_MovePower = dir * (m_MovePowerLimit * distRatio);
            }
        }
    }
}
