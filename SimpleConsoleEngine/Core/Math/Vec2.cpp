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
    : m_X(0.0f)
    , m_Y(0.0f)
{
}

Vec2::Vec2(float x, float y) noexcept
    : m_X(x)
    , m_Y(y)
{
}


float Vec2::GetX() const noexcept
{
    return m_X;
}

float Vec2::GetY() const noexcept
{
    return m_Y;
}

void Vec2::SetX(float x) noexcept
{
    m_X = x;
}

void Vec2::SetY(float y) noexcept
{
    m_Y = y;
}

void Vec2::Set(float x, float y) noexcept
{
    m_X = x;
    m_Y = y;
}

void Vec2::SetZero() noexcept
{
    Set(0.0f, 0.0f);
}


float Vec2::Length() const noexcept
{
    return std::hypotf(m_X, m_Y);
}

float Vec2::LengthSquared() const noexcept
{
    return m_X * m_X + m_Y * m_Y;
}

float Vec2::Distance(const Vec2& other) const noexcept
{
    return std::hypotf(other.m_X - m_X, other.m_Y - m_Y);
}

float Vec2::DistanceSquared(const Vec2& other) const noexcept
{
    float dx = other.m_X - m_X;
    float dy = other.m_Y - m_Y;
    return dx * dx + dy * dy;
}

Vec2 Vec2::Direction(const Vec2& other) const noexcept
{
    return (other - *this).Normalize();
}

Vec2& Vec2::Normalize() noexcept
{
    return *this /= Length();
}

Vec2 Vec2::GetNormalized() const noexcept
{
    return *this / Length();
}


Vec2 Vec2::operator+(const Vec2 &v) const noexcept
{
    return Vec2(m_X + v.m_X, m_Y + v.m_Y);
}

Vec2 Vec2::operator-(const Vec2 &v) const noexcept
{
    return Vec2(m_X - v.m_X, m_Y - v.m_Y);
}

Vec2 Vec2::operator*(float s) const noexcept
{
    return Vec2(m_X * s, m_Y * s);
}

Vec2 Vec2::operator/(float s) const noexcept
{
    return Vec2(m_X / s, m_Y / s);
}

Vec2 Vec2::operator-() const noexcept
{
    return Vec2(-m_X, -m_Y);
}


Vec2& Vec2::operator+=(const Vec2 &v) noexcept
{
    m_X += v.m_X; m_Y += v.m_Y;
    return *this;
}

Vec2& Vec2::operator-=(const Vec2 &v) noexcept
{
    m_X -= v.m_X; m_Y -= v.m_Y;
    return *this;
}

Vec2& Vec2::operator*=(float s) noexcept
{
    m_X *= s;
    m_Y *= s;
    return *this;
}

Vec2& Vec2::operator/=(float s) noexcept
{
    m_X /= s;
    m_Y /= s;
    return *this;
}


bool Vec2::operator==(const Vec2 &v) const noexcept
{
    return m_X == v.m_X && m_Y == v.m_Y;
}

bool Vec2::operator!=(const Vec2 &v) const noexcept
{
    return m_X != v.m_X || m_Y != v.m_Y;
}

SCE_END
