#pragma once
SCE_START


class Vec2
{
public:
    static const Vec2 ZERO;
    static const Vec2 ONE;
    static const Vec2 UP;
    static const Vec2 DOWN;
    static const Vec2 LEFT;
    static const Vec2 RIGHT;

public:
    Vec2()                                          noexcept;
    Vec2(float _x, float _y)                        noexcept;

    float   GetX()                          const   noexcept;
    float   GetY()                          const   noexcept;
    void    SetX(float _x)                          noexcept;
    void    SetY(float _y)                          noexcept;
    void    Set(float _x, float _y)                 noexcept;
    void    SetZero()                               noexcept;

    float   Length()                        const   noexcept;
    float   LengthSquared()                 const   noexcept;
    float   Distance(const Vec2& _v)        const   noexcept;
    float   DistanceSquared(const Vec2& _v) const   noexcept;
    Vec2    Direction(const Vec2& _v)       const   noexcept;
    Vec2&   Normalize()                             noexcept;
    Vec2    GetNormalized()                 const   noexcept;

    Vec2    operator+(const Vec2 &_v)       const   noexcept;
    Vec2    operator-(const Vec2 &_v)       const   noexcept;
    Vec2    operator*(float _s)             const   noexcept;
    Vec2    operator/(float _s)             const   noexcept;
    Vec2    operator-()                     const   noexcept;

    Vec2&   operator+=(const Vec2 &_v)              noexcept;
    Vec2&   operator-=(const Vec2 &_v)              noexcept;
    Vec2&   operator*=(float _s)                    noexcept;
    Vec2&   operator/=(float _s)                    noexcept;

    bool    operator==(const Vec2 &_v)      const   noexcept;
    bool    operator!=(const Vec2 &_v)      const   noexcept;

private:
    float   x;
    float   y;
};

SCE_END
