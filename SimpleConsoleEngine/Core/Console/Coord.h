#pragma once
SCE_START
class Vec2;

/////////////////////////////////////////////////////////////////////////////////////////
struct Coord
{
    static Vec2 ConvertToVec2(const Coord& _coord) noexcept;

    Coord() noexcept;
    Coord(const Vec2& _vec2) noexcept;

    template<typename T, typename U>
    constexpr Coord(T _x, U _y) noexcept;

    short x;
    short y;
};

/////////////////////////////////////////////////////////////////////////////////////////
template<typename T, typename U>
constexpr Coord::Coord(T _x, U _y) noexcept
    : x(Safe::IntegralCast<decltype(x)>(_x))
    , y(Safe::IntegralCast<decltype(y)>(_y))
{
}

SCE_END
