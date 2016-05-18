#include "stdafx.h"
#include "Hero.h"
//----------------------------------------------------------------------------------------------------
#include "SimpleConsoleEngine/Core/Console/Shape.hpp"
#include "SimpleConsoleEngine/Core/Timer/Timer.h"
//----------------------------------------------------------------------------------------------------
#include "Object/Dummy.h"
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
}

void Hero::Release()
{
    Unit::Release();
}

void Hero::Update(float dt)
{
    static Color color = GetColor();
    static Timer timer(0.1f);
    timer.AccumDt(dt);
    if (timer.DurationCheck())
    {
        SetColor(++color);
    }
    Unit::Update(dt);
}

void Hero::Render()
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
        auto x = static_cast<short>(temp.m_X * 2.0f);
        auto y = static_cast<short>(temp.m_Y);
        dummy.SetCoord(Coord(x, y));
        dummy.Render();
    }

    Unit::Render();
}
