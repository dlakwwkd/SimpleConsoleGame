#pragma once
#include "Console.h"
SCE_START


class SCE_API Shape
{
    SPECIALFUNC_SET(Shape, default)
public:
    Shape() noexcept
    :   m_Form(L' '),
        m_Color(Color::WHITE),
        m_BGColor(Color::BLACK)
    {
    }
    Shape(const wchar_t& data, const Color& color = Color::WHITE, const Color& bgColor = Color::BLACK) noexcept
    :   m_Form(data),
        m_Color(color),
        m_BGColor(bgColor)
    {
    }
    virtual ~Shape() = default;

    inline void     SetForm(wchar_t form) noexcept { m_Form = form; }
    inline void     SetColor(Color color) noexcept { m_Color = color; }
    inline void     SetBGColor(Color bgColor) noexcept { m_BGColor = bgColor; }
    inline wchar_t  GetForm() const noexcept { return m_Form; }
    inline Color    GetColor() const noexcept { return m_Color; }
    inline Color    GetBGColor() const noexcept { return m_BGColor; }

    inline void Render(const Coord& pos, BYTE depth = 0) noexcept
    {
        auto& console = Console::GetInstance();
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
