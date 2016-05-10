#pragma once
#include "Console.h"
SCE_START


class SCE_API Shape
{
    SPECIALFUNC_SET(Shape, default)
public:
    Shape() noexcept : m_Data(L' '), m_Color(Color::WHITE), m_BGColor(Color::BLACK) {}
    Shape(const wchar_t& data, const Color& color, const Color& bgColor) noexcept
    :   m_Data(data),
        m_Color(color),
        m_BGColor(bgColor)
    {
    }
    virtual ~Shape() = default;

    inline void Render(const Coord& pos) const noexcept
    {
        const auto& console = Console::GetInstance();
        console.SetColor(m_Color, m_BGColor);
        console.Print(pos, m_Data);
    }

private:
    wchar_t m_Data;
    Color   m_Color;
    Color   m_BGColor;
};

SCE_END
