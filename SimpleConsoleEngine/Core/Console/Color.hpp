#pragma once
SCE_START


enum class Color : unsigned short
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


inline Color& operator++(Color& _color) noexcept
{
    auto idx = static_cast<unsigned short>(_color);
    if (++idx == static_cast<unsigned short>(Color::GREY))
    {
        _color = Color::BLACK;
    }
    else if (idx > static_cast<unsigned short>(Color::WHITE))
    {
        _color = Color::GREY;
    }
    else
    {
        _color = static_cast<Color>(idx);
    }
    return _color;
}

inline Color DarkenColor(Color _color) noexcept
{
    auto idx = static_cast<unsigned short>(_color);
    auto comp = static_cast<unsigned short>(Color::GREY);
    return idx < comp ? _color : static_cast<Color>(idx - comp);
}

SCE_END
