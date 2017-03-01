#include "stdafx.h"
#include "Coord.h"
#include "../Math/Vec2.h"
SCE_USE

/////////////////////////////////////////////////////////////////////////////////////////
Vec2 Coord::ConvertToVec2(const Coord& _coord) noexcept
{
    return
    {
        static_cast<float>(_coord.x) * 0.5f,
        static_cast<float>(_coord.y)
    };
}

/////////////////////////////////////////////////////////////////////////////////////////
Coord::Coord() noexcept
    : x{}
    , y{}
{
}

/////////////////////////////////////////////////////////////////////////////////////////
Coord::Coord(const Vec2& _vec2) noexcept
    : x{ static_cast<decltype(x)>(_vec2.GetX() * 2.0f) }
    , y{ static_cast<decltype(y)>(_vec2.GetY()) }
{
}
