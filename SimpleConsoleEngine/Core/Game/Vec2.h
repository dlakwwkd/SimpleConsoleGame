#pragma once
#include "../Console/Coord.hpp"
SCE_START


class SCE_API Vec2
{
    SPECIALFUNC_SET(Vec2, default)
public:
    Vec2() noexcept
    :   m_X(0.0f),
        m_Y(0.0f)
    {
    }
    Vec2(float x, float y) noexcept
    :   m_X(x),
        m_Y(y)
    {
    }
    inline Vec2(const Coord& coord) noexcept;

    inline void     Set(float x, float y) noexcept;
    inline void     SetZero() noexcept;
    inline float    Length() const noexcept;
    inline float    LengthSquared() const noexcept;
    inline float    Distance(const Vec2& other) const noexcept;
    inline float    DistanceSquared(const Vec2& other) const noexcept;
    inline Vec2     Direction(const Vec2& other) const noexcept;
    inline Vec2&    Normalize() noexcept;
    inline Vec2     GetNormalized() noexcept;

    inline Vec2     operator+   (const Vec2 &v) const noexcept;
    inline Vec2     operator-   (const Vec2 &v) const noexcept;
    inline Vec2     operator*   (float s)       const noexcept;
    inline Vec2     operator/   (float s)       const noexcept;
    inline Vec2     operator-   ()              const noexcept;

    inline Vec2&    operator+=  (const Vec2 &v) noexcept;
    inline Vec2&    operator-=  (const Vec2 &v) noexcept;
    inline Vec2&    operator*=  (float s)       noexcept;
    inline Vec2&    operator/=  (float s)       noexcept;

    inline bool     operator==  (const Vec2 &v) const noexcept;
    inline bool     operator!=  (const Vec2 &v) const noexcept;

public:
    float m_X;
    float m_Y;

    static const Vec2 ZERO;
    static const Vec2 ONE;
    static const Vec2 UP;
    static const Vec2 DOWN;
    static const Vec2 LEFT;
    static const Vec2 RIGHT;
};

SCE_END
#include "Vec2.inl"
