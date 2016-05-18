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
    Unit::Render();
}
