#include "stdafx.h"
#include "Hero.h"
//----------------------------------------------------------------------------------------------------
#include "SimpleConsoleEngine/Core/Console/Shape.hpp"
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
    static float limit = 0.1f;
    static float stack = 0.0f;
    stack += dt;
    if (stack > limit)
    {
        SetColor(++color);
        stack = 0.0f;
    }
    Unit::Update(dt);
}

void Hero::Render()
{
    Unit::Render();
}
