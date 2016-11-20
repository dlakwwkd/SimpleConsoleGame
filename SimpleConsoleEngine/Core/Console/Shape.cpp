#include "stdafx.h"
#include "Shape.h"
#include "Coord.h"
#include "Console.h"
SCE_START


Shape::Shape() noexcept
    : m_Form(L' ')
    , m_Color(Color::WHITE)
    , m_BGColor(Color::BLACK)
{
}

Shape::Shape(wchar_t data, Color color, Color bgColor) noexcept
    : m_Form(data)
    , m_Color(color)
    , m_BGColor(bgColor)
{
}


wchar_t Shape::GetForm() const noexcept
{
    return m_Form;
}

Color Shape::GetColor() const noexcept
{
    return m_Color;
}

Color Shape::GetBGColor() const noexcept
{
    return m_BGColor;
}


void Shape::SetForm(wchar_t form) noexcept
{
    m_Form = form;
}

void Shape::SetColor(Color color) noexcept
{
    m_Color = color;
}

void Shape::SetBGColor(Color bgColor) noexcept
{
    m_BGColor = bgColor;
}


void Shape::Render(const Coord& pos, BYTE depth) noexcept
{
    static auto& console = Console::GetInstance();
    if (console.DepthCheck(pos, depth))
    {
        console.SetColor(m_Color, m_BGColor);
        console.Print(pos, m_Form);
    }
}

SCE_END
