#include "stdafx.h"
#include "Coord.h"
#include "../Math/Vec2.h"
SCE_START


Coord::Coord() noexcept
    : m_X(0)
    , m_Y(0)
{
}

Coord::Coord(const Vec2& vec2) noexcept
    : m_X(static_cast<decltype(m_X)>(vec2.GetX() * 2.0f))
    , m_Y(static_cast<decltype(m_Y)>(vec2.GetY()))
{
}


Vec2 Coord::ConvertToVec2(const Coord& coord) noexcept
{
    return Vec2(
        static_cast<float>(coord.m_X) * 0.5f,
        static_cast<float>(coord.m_Y));
}

SCE_END
