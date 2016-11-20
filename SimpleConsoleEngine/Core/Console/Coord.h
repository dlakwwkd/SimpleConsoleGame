#pragma once
SCE_START
class Vec2;


struct Coord
{
    short m_X;
    short m_Y;

    Coord() noexcept;
    Coord(const Vec2& vec2) noexcept;

    template<typename T>
    constexpr Coord(T x, T y) noexcept;

    static Vec2 ConvertToVec2(const Coord& coord) noexcept;
};


template<typename T>
constexpr Coord::Coord(T x, T y) noexcept
    : m_X(Safe::IntegralCast<decltype(m_X)>(x))
    , m_Y(Safe::IntegralCast<decltype(m_Y)>(y))
{
}

SCE_END
