#pragma once
#include "../Math/Vec2.h"
SCE_START


struct SCE_API Coord
{
    short m_X;
    short m_Y;

    Coord() noexcept
    :   m_X(0),
        m_Y(0)
    {
    }
    template<typename T>
    constexpr Coord(T x, T y) noexcept
    :   m_X(Safe::IntegralCast<decltype(m_X)>(x)),
        m_Y(Safe::IntegralCast<decltype(m_Y)>(y))
    {
    }

    static Vec2 ConvertToVec2(const Coord& coord)
    {
        return Vec2(
            static_cast<float>(coord.m_X) * 0.5f,
            static_cast<float>(coord.m_Y));
    }
};

SCE_END
