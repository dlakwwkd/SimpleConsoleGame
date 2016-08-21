#include "stdafx.h"
#include "Hero.h"
//----------------------------------------------------------------------------------------------------
#include "SimpleConsoleEngine/Core/Console/Shape.hpp"
#include "SimpleConsoleEngine/Core/Timer/Timer.h"
//----------------------------------------------------------------------------------------------------
#include "../Dummy.h"
SCE_USE


Hero::Hero()
{
    Init();
}


Hero::~Hero()
{
    Release();
}

void Hero::Init()
{
    Unit::Init();
    SetShape(Shape(L'▣', Color::GREEN));
    SetDepth(5);
    m_MovePowerLimit = 0.2f;
    m_MovePowerFrict = 5.0f;
    m_Speed = 50.0f;
}

void Hero::Release()
{
    Unit::Release();
}

void Hero::Update(float dt)
{
    static Color color = GetColor();
    static Timer timer(1.0f);
    timer.AccumDt(dt);
    if (timer.DurationCheck())
    {
        SetColor(++color);

        std::thread([]()
        {
            Beep(524, 120);
            Beep(660, 120);
            Beep(784, 120);
        }
        ).detach();
    }
    Unit::Update(dt);
}

void Hero::Render()
{
    Unit::Render();
}
