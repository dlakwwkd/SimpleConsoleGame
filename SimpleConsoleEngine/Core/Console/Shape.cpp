#include "stdafx.h"
#include "Shape.h"
#include "Coord.h"
#include "Console.h"
SCE_USE

/////////////////////////////////////////////////////////////////////////////////////////
Shape::Shape() noexcept
    : form{ L' ' }
    , color{ Color::WHITE }
    , bgColor{ Color::BLACK }
{
}

/////////////////////////////////////////////////////////////////////////////////////////
Shape::Shape(wchar_t _form, Color _color, Color _bgColor) noexcept
    : form{ _form }
    , color{ _color }
    , bgColor{ _bgColor }
{
}

/////////////////////////////////////////////////////////////////////////////////////////
void Shape::Render(const Coord& _pos, BYTE _depth) noexcept
{
    static auto& console = Console::GetInstance();
    if (console.DepthCheck(_pos, _depth))
    {
        console.StoreShape(_pos, *this);
    }
}
