#include "stdafx.h"
#include "Vec2.h"
SCE_USE

const Vec2 Vec2::ZERO   = {  0.f,  0.f };
const Vec2 Vec2::ONE    = {  1.f,  1.f };
const Vec2 Vec2::UP     = {  0.f, -1.f };
const Vec2 Vec2::DOWN   = {  0.f, +1.f };
const Vec2 Vec2::LEFT   = { -1.f,  0.f };
const Vec2 Vec2::RIGHT  = { +1.f,  0.f };

/////////////////////////////////////////////////////////////////////////////////////////
float Vec2::Length() const noexcept
{
    return std::sqrt(LengthSquared());
}

/////////////////////////////////////////////////////////////////////////////////////////
float Vec2::Distance(const Vec2& _v) const noexcept
{
    return std::sqrt(DistanceSquared(_v));
}

/////////////////////////////////////////////////////////////////////////////////////////
Vec2& Vec2::Normalize() noexcept
{
    return *this /= Length();
}

/////////////////////////////////////////////////////////////////////////////////////////
Vec2 Vec2::GetNormalized() const noexcept
{
    return *this / Length();
}

/////////////////////////////////////////////////////////////////////////////////////////
Vec2 Vec2::Direction(const Vec2& _v) const noexcept
{
    return (_v - *this).GetNormalized();
}
