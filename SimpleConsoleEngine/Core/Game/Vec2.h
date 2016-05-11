#pragma once
#include "../Console/Coord.hpp"
SCE_START


class SCE_API Vec2
{
    SPECIALFUNC_SET(Vec2, default)
public:
    Vec2() noexcept : m_X(0.0f), m_Y(0.0f) {}
    Vec2(float x, float y) noexcept : m_X(x), m_Y(y) {}
    inline Vec2(const Coord& coord) noexcept;

    const Vec2  operator+   (const Vec2 &v) const noexcept  { return Vec2(); }
    Vec2&       operator+=  (const Vec2 &v) noexcept        { m_X += v.m_X; m_Y += v.m_Y; return *this; }
    const Vec2  operator-   (const Vec2 &v) const noexcept  { return Vec2(); }
    Vec2&       operator-=  (const Vec2 &v) noexcept        { return *this; }
    const Vec2  operator*   (float s)       const noexcept  { return Vec2(); }
    Vec2&       operator*=  (float s)       noexcept        { return *this; }
    const Vec2  operator/   (float s)       const noexcept  { return Vec2(); }
    const Vec2  operator-   ()              const noexcept  { return Vec2(); }
    bool        operator<   (const Vec2 &v) const noexcept  { return false; }
    bool        operator==  (const Vec2 &v) const noexcept  { return false; }
    bool        operator!=  (const Vec2 &v) const noexcept  { return false; }
    
private:
    float m_X;
    float m_Y;
};

SCE_END
#include "Vec2.inl"
