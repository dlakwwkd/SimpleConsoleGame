#include "stdafx.h"
#include "Vec2.h"
SCE_START

const Vec2 Vec2::ZERO   = { 0.0f, 0.0f };
const Vec2 Vec2::ONE    = { 1.0f, 1.0f };
const Vec2 Vec2::UP     = { 0.0f, -1.0f };
const Vec2 Vec2::DOWN   = { 0.0f, +1.0f };
const Vec2 Vec2::LEFT   = { -1.0f, 0.0f };
const Vec2 Vec2::RIGHT  = { +1.0f, 0.0f };


Vec2::Vec2() noexcept
    : x{}
    , y{}
{
}

Vec2::Vec2(float _x, float _y) noexcept
    : x{ _x }
    , y{ _y }
{
}


float Vec2::GetX() const noexcept
{
    return x;
}

float Vec2::GetY() const noexcept
{
    return y;
}

void Vec2::SetX(float _x) noexcept
{
    x = _x;
}

void Vec2::SetY(float _y) noexcept
{
    y = _y;
}

void Vec2::Set(float _x, float _y) noexcept
{
    x = _x;
    y = _y;
}

void Vec2::SetZero() noexcept
{
    Set(0.0f, 0.0f);
}


float Vec2::Length() const noexcept
{
    return std::hypotf(x, y);
}

float Vec2::LengthSquared() const noexcept
{
    return x * x + y * y;
}

float Vec2::Distance(const Vec2& _v) const noexcept
{
    return std::hypotf(_v.x - x, _v.y - y);
}

float Vec2::DistanceSquared(const Vec2& _v) const noexcept
{
    float dx = _v.x - x;
    float dy = _v.y - y;
    return dx * dx + dy * dy;
}

Vec2 Vec2::Direction(const Vec2& _v) const noexcept
{
    return (_v - *this).Normalize();
}

Vec2& Vec2::Normalize() noexcept
{
    return *this /= Length();
}

Vec2 Vec2::GetNormalized() const noexcept
{
    return *this / Length();
}


Vec2 Vec2::operator+(const Vec2&_v) const noexcept
{
    return Vec2(x + _v.x, y + _v.y);
}

Vec2 Vec2::operator-(const Vec2&_v) const noexcept
{
    return Vec2(x - _v.x, y - _v.y);
}

Vec2 Vec2::operator*(float _s) const noexcept
{
    return Vec2(x * _s, y * _s);
}

Vec2 Vec2::operator/(float _s) const noexcept
{
    return Vec2(x / _s, y / _s);
}

Vec2 Vec2::operator-() const noexcept
{
    return Vec2(-x, -y);
}


Vec2& Vec2::operator+=(const Vec2&_v) noexcept
{
    x += _v.x;
    y += _v.y;
    return *this;
}

Vec2& Vec2::operator-=(const Vec2&_v) noexcept
{
    x -= _v.x;
    y -= _v.y;
    return *this;
}

Vec2& Vec2::operator*=(float _s) noexcept
{
    x *= _s;
    y *= _s;
    return *this;
}

Vec2& Vec2::operator/=(float _s) noexcept
{
    x /= _s;
    y /= _s;
    return *this;
}


bool Vec2::operator==(const Vec2&_v) const noexcept
{
    return x == _v.x && y == _v.y;
}

bool Vec2::operator!=(const Vec2&_v) const noexcept
{
    return x != _v.x || y != _v.y;
}

SCE_END
