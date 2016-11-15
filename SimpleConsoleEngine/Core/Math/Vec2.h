#pragma once
SCE_START


class Vec2
{
    SPECIALFUNC_SET(Vec2, default)
public:
    Vec2() noexcept;
    Vec2(float x, float y) noexcept;

    float    GetX() const noexcept;
    float    GetY() const noexcept;
    void     SetX(float x) noexcept;
    void     SetY(float y) noexcept;
    void     Set(float x, float y) noexcept;
    void     SetZero() noexcept;

    float    Length() const noexcept;
    float    LengthSquared() const noexcept;
    float    Distance(const Vec2& other) const noexcept;
    float    DistanceSquared(const Vec2& other) const noexcept;
    Vec2     Direction(const Vec2& other) const noexcept;
    Vec2&    Normalize() noexcept;
    Vec2     GetNormalized() const noexcept;

    Vec2     operator+(const Vec2 &v) const noexcept;
    Vec2     operator-(const Vec2 &v) const noexcept;
    Vec2     operator*(float s) const noexcept;
    Vec2     operator/(float s) const noexcept;
    Vec2     operator-() const noexcept;

    Vec2&    operator+=(const Vec2 &v) noexcept;
    Vec2&    operator-=(const Vec2 &v) noexcept;
    Vec2&    operator*=(float s) noexcept;
    Vec2&    operator/=(float s) noexcept;

    bool     operator==(const Vec2 &v) const noexcept;
    bool     operator!=(const Vec2 &v) const noexcept;

public:
    static const Vec2 ZERO;
    static const Vec2 ONE;
    static const Vec2 UP;
    static const Vec2 DOWN;
    static const Vec2 LEFT;
    static const Vec2 RIGHT;

private:
    float m_X;
    float m_Y;
};

SCE_END
