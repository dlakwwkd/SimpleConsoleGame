#include "stdafx.h"
#include "Hero.h"
#include "Dummy.h"
#include "Core/Console/Shape.hpp"
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
    SetShape(Shape(L'▣', Color::GREEN));
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
    Object::Render();
}

