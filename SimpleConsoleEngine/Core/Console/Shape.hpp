#pragma once
#include "Console.h"
SCE_START


class Shape
{
    SPECIALFUNC_SET(Shape, default)
public:
    Shape() noexcept
    :   m_Form(L' '),
        m_Color(Color::WHITE),
        m_BGColor(Color::BLACK)
    {
    }
    Shape(wchar_t data, Color color = Color::WHITE, Color bgColor = Color::BLACK) noexcept
    :   m_Form(data),
        m_Color(color),
        m_BGColor(bgColor)
    {
    }

    void    SetForm(wchar_t form) noexcept { m_Form = form; }
    void    SetColor(Color color) noexcept { m_Color = color; }
    void    SetBGColor(Color bgColor) noexcept { m_BGColor = bgColor; }
    wchar_t GetForm() const noexcept { return m_Form; }
    Color   GetColor() const noexcept { return m_Color; }
    Color   GetBGColor() const noexcept { return m_BGColor; }

    void    Render(const Coord& pos, BYTE depth = 0) noexcept
    {
        static auto& console = Console::GetInstance();
        if (console.DepthCheck(pos, depth))
        {
            console.SetColor(m_Color, m_BGColor);
            console.Print(pos, m_Form);
        }
    }

private:
    wchar_t m_Form;
    Color   m_Color;
    Color   m_BGColor;
};

SCE_END
