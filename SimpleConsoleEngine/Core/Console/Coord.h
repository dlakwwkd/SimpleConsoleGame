#pragma once
#include "../Math/Vec2.h"
SCE_START

/////////////////////////////////////////////////////////////////////////////////////////
struct Coord
{
    template<typename T, typename U>
    constexpr Coord(T _x, U _y) noexcept;
    constexpr Coord(const Vec2& _vec2) noexcept;
    constexpr Coord() noexcept;
    constexpr Vec2 ConvertToVec2() const noexcept;

    short x;
    short y;
};

/////////////////////////////////////////////////////////////////////////////////////////
template<typename T, typename U>
constexpr Coord::Coord(T _x, U _y) noexcept
    : x{ Safe::IntegralCast<decltype(x)>(_x) }
    , y{ Safe::IntegralCast<decltype(y)>(_y) }
{
}

/////////////////////////////////////////////////////////////////////////////////////////
constexpr Coord::Coord(const Vec2& _vec2) noexcept
    : x{ static_cast<decltype(x)>(_vec2.GetX() * 2.f) }
    , y{ static_cast<decltype(y)>(_vec2.GetY()) }
{
}

/////////////////////////////////////////////////////////////////////////////////////////
constexpr Coord::Coord() noexcept
    : x{}
    , y{}
{
}

/////////////////////////////////////////////////////////////////////////////////////////
constexpr Vec2 Coord::ConvertToVec2() const noexcept
{
    return
    {
        static_cast<float>(x) * 0.5f,
        static_cast<float>(y)
    };
}

SCE_END
