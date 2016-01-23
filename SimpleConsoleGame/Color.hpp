#pragma once
enum class Color : WORD
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

inline Color& operator++(Color& color)
{
    auto idx = static_cast<WORD>(color);
    if (++idx == static_cast<WORD>(Color::GREY))
        color = Color::BLACK;
    else if (idx > static_cast<WORD>(Color::WHITE))
        color = Color::GREY;
    else
        color = static_cast<Color>(idx);
    return color;
}

inline Color DarkenColor(const Color& color)
{
    auto idx = static_cast<WORD>(color);
    auto comp = static_cast<WORD>(Color::GREY);
    return idx < comp ? color : static_cast<Color>(idx - comp);
}
