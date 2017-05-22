#include "stdafx.h"
#include "Shape.h"
#include "Coord.h"
#include "Console.h"
#include "../Game/GameManager.h"
#include "../Math/Vec2.h"
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
    static auto& gm = GameManager::GetInstance();
    static auto& console = Console::GetInstance();

    Coord fixedPos = Coord::ConvertToVec2(_pos) - gm.GetCameraPos();
    fixedPos.x += console.GetScreenWidth() / 2;
    fixedPos.y += console.GetScreenHeight() / 2;

    if (console.DepthCheck(fixedPos, _depth))
    {
        console.StoreShape(fixedPos, *this);
    }
}
