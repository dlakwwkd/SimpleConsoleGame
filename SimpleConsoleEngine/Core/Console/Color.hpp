#pragma once
SCE_START

/////////////////////////////////////////////////////////////////////////////////////////
enum Color : unsigned short
{
    BLACK = 0,

    DARK_BLUE,
    DARK_GREEN,
    DARK_CYAN,
    DARK_RED,
    DARK_MAGENTA,
    DARK_YELLOW,
    DARK_WHITE,

    GREY,

    BLUE,
    GREEN,
    CYAN,
    RED,
    MAGENTA,
    YELLOW,
    WHITE,
};

/////////////////////////////////////////////////////////////////////////////////////////
inline Color& operator++(Color& _color) noexcept
{
    Color idx = _color;
    if (++idx == Color::GREY)
    {
        _color = Color::BLACK;
    }
    else if (idx > Color::WHITE)
    {
        _color = Color::GREY;
    }
    else
    {
        _color = idx;
    }
    return _color;
}

/////////////////////////////////////////////////////////////////////////////////////////
inline Color DarkenColor(Color _color) noexcept
{
    if (_color < Color::GREY)
        return _color;

    return static_cast<Color>(_color - Color::GREY);
}

SCE_END
