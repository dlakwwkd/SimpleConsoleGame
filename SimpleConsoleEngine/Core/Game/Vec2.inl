#pragma once
SCE_START


inline Vec2::Vec2(const Coord& coord) noexcept
{
    m_X = static_cast<float>(coord.m_X);
    m_Y = static_cast<float>(coord.m_Y);
}



SCE_END


