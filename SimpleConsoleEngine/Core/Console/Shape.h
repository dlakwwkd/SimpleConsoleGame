#pragma once
#include "Color.hpp"
SCE_START
struct Coord;


class Shape
{
public:
    Shape() noexcept;
    Shape(wchar_t data, Color color = Color::WHITE, Color bgColor = Color::BLACK) noexcept;

    wchar_t GetForm() const noexcept;
    Color   GetColor() const noexcept;
    Color   GetBGColor() const noexcept;

    void    SetForm(wchar_t form) noexcept;
    void    SetColor(Color color) noexcept;
    void    SetBGColor(Color bgColor) noexcept;

    void    Render(const Coord& pos, BYTE depth = 0) noexcept;

private:
    wchar_t m_Form;
    Color   m_Color;
    Color   m_BGColor;
};

SCE_END
