#include "Vec2.h"
#pragma once
SCE_START


inline Vec2::Vec2(Coord&& coord) noexcept
{
    m_X = static_cast<float>(coord.m_X / 2);
    m_Y = static_cast<float>(coord.m_Y);
}

inline void Vec2::Set(float x, float y) noexcept
{
    m_X = x;
    m_Y = y;
}

inline void Vec2::SetZero() noexcept
{
    Set(0.0f, 0.0f);
}

inline float Vec2::Length() const noexcept
{
    return std::hypotf(m_X, m_Y);
}

inline float Vec2::LengthSquared() const noexcept
{
    return m_X * m_X + m_Y * m_Y;
}

inline float Vec2::Distance(const Vec2& other) const noexcept
{
    return std::hypotf(other.m_X - m_X, other.m_Y - m_Y);
}

inline float Vec2::DistanceSquared(const Vec2& other) const noexcept
{
    float dx = other.m_X - m_X;
    float dy = other.m_Y - m_Y;
    return dx * dx + dy * dy;
}

inline Vec2 Vec2::Direction(const Vec2& other) const noexcept
{
    return (other - *this).Normalize();
}

inline Vec2& Vec2::Normalize() noexcept
{
    return *this /= Length();
}



inline Vec2     Vec2::operator+ (const Vec2 &v) const noexcept  { return Vec2(m_X + v.m_X, m_Y + v.m_Y); }
inline Vec2     Vec2::operator- (const Vec2 &v) const noexcept  { return Vec2(m_X - v.m_X, m_Y - v.m_Y); }
inline Vec2     Vec2::operator* (float s)       const noexcept  { return Vec2(m_X * s, m_Y * s); }
inline Vec2     Vec2::operator/ (float s)       const noexcept  { return Vec2(m_X / s, m_Y / s); }
inline Vec2     Vec2::operator- ()              const noexcept  { return Vec2(-m_X, -m_Y); }

inline Vec2&    Vec2::operator+=(const Vec2 &v) noexcept        { m_X += v.m_X; m_Y += v.m_Y;   return *this; }
inline Vec2&    Vec2::operator-=(const Vec2 &v) noexcept        { m_X -= v.m_X; m_Y -= v.m_Y;   return *this; }
inline Vec2&    Vec2::operator*=(float s)       noexcept        { m_X *= s;     m_Y *= s;       return *this; }
inline Vec2&    Vec2::operator/=(float s)       noexcept        { m_X /= s;     m_Y /= s;       return *this; }

inline bool     Vec2::operator==(const Vec2 &v) const noexcept  { return m_X == v.m_X && m_Y == v.m_Y; }
inline bool     Vec2::operator!=(const Vec2 &v) const noexcept  { return m_X != v.m_X || m_Y != v.m_Y; }

SCE_END


