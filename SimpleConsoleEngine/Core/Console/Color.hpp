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



inline Color& operator++(Color& color) noexcept
{
    auto idx = static_cast<unsigned short>(color);
    if (++idx == static_cast<unsigned short>(Color::GREY))
        color = Color::BLACK;
    else if (idx > static_cast<unsigned short>(Color::WHITE))
        color = Color::GREY;
    else
        color = static_cast<Color>(idx);
    return color;
}

inline Color DarkenColor(Color color) noexcept
{
    auto idx = static_cast<unsigned short>(color);
    auto comp = static_cast<unsigned short>(Color::GREY);
    return idx < comp ? color : static_cast<Color>(idx - comp);
}

SCE_END
