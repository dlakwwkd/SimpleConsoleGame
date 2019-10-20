#pragma once
SCE_START

/////////////////////////////////////////////////////////////////////////////////////////
class Vec2
{
public:
    constexpr Vec2() noexcept;
    constexpr Vec2(float _x, float _y) noexcept;

    constexpr float     GetX() const noexcept;
    constexpr float     GetY() const noexcept;
    constexpr void      SetX(float _x) noexcept;
    constexpr void      SetY(float _y) noexcept;
    constexpr void      Set(float _x, float _y) noexcept;
    constexpr void      SetZero() noexcept;

    constexpr float     LengthSquared() const noexcept;
    constexpr float     DistanceSquared(const Vec2& _v) const noexcept;

    constexpr bool      operator==(const Vec2& _v) const noexcept;
    constexpr bool      operator!=(const Vec2& _v) const noexcept;
    constexpr Vec2      operator+(const Vec2& _v) const noexcept;
    constexpr Vec2      operator-(const Vec2& _v) const noexcept;
    constexpr Vec2      operator*(float _s) const noexcept;
    constexpr Vec2      operator/(float _s) const noexcept;
    constexpr Vec2      operator-() const noexcept;
    constexpr Vec2&     operator+=(const Vec2& _v) noexcept;
    constexpr Vec2&     operator-=(const Vec2& _v) noexcept;
    constexpr Vec2&     operator*=(float _s) noexcept;
    constexpr Vec2&     operator/=(float _s) noexcept;

public:
    float               Length() const noexcept;
    float               Distance(const Vec2& _v) const noexcept;
    Vec2&               Normalize() noexcept;
    Vec2                GetNormalized() const noexcept;
    Vec2                Direction(const Vec2& _v) const noexcept;

public:
    static const Vec2   ZERO;
    static const Vec2   ONE;
    static const Vec2   UP;
    static const Vec2   DOWN;
    static const Vec2   LEFT;
    static const Vec2   RIGHT;

private:
    float               x;
    float               y;
};

SCE_END
#include "Vec2.inl"
