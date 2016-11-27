#include "stdafx.h"
#include "Shape.h"
#include "Coord.h"
#include "Console.h"
SCE_START


Shape::Shape() noexcept
    : form{ L' ' }
    , color{ Color::WHITE }
    , bgColor{ Color::BLACK }
{
}


void Shape::Render(const Coord& _pos, BYTE _depth) noexcept
{
    static auto& console = Console::GetInstance();
    if (console.DepthCheck(_pos, _depth))
    {
        console.StoreShape(_pos, *this);
    }
}

SCE_END
