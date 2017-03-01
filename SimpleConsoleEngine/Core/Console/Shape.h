#pragma once
#include "Color.hpp"
SCE_START
struct Coord;

/////////////////////////////////////////////////////////////////////////////////////////
struct Shape
{
    Shape() noexcept;
    Shape(
        wchar_t _form,
        Color _color = Color::WHITE,
        Color _bgColor = Color::BLACK) noexcept;

    void    Render(const Coord& _pos, BYTE _depth = 0) noexcept;

    wchar_t form;
    Color   color;
    Color   bgColor;
};

SCE_END
