#pragma once
#include "Color.hpp"
SCE_START
struct Coord;


class Shape
{
    SPECIALFUNC_SET(Shape, default)
public:
    Shape();
    Shape(wchar_t data, Color color = Color::WHITE, Color bgColor = Color::BLACK);

    wchar_t GetForm() const;
    Color   GetColor() const;
    Color   GetBGColor() const;

    void    SetForm(wchar_t form);
    void    SetColor(Color color);
    void    SetBGColor(Color bgColor);

    void    Render(const Coord& pos, BYTE depth = 0);

private:
    wchar_t m_Form;
    Color   m_Color;
    Color   m_BGColor;
};

SCE_END
