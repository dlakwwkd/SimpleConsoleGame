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
inline constexpr Color DarkenColor(Color _color) noexcept
{
    if (_color < Color::GREY)
        return _color;

    return static_cast<Color>(_color - Color::GREY);
}

/////////////////////////////////////////////////////////////////////////////////////////
inline constexpr COLORREF GetRGBColor(Color _color) noexcept
{
    switch (_color)
    {
    case Color::BLACK:          return RGB(0,   0,   0  );  break;
    case Color::DARK_BLUE:      return RGB(0,   0,   200);  break;
    case Color::DARK_GREEN:     return RGB(0,   200, 0  );  break;
    case Color::DARK_CYAN:      return RGB(0,   200, 200);  break;
    case Color::DARK_RED:       return RGB(200, 0,   0  );  break;
    case Color::DARK_MAGENTA:   return RGB(200, 0,   200);  break;
    case Color::DARK_YELLOW:    return RGB(200, 200, 0  );  break;
    case Color::DARK_WHITE:     return RGB(200, 200, 200);  break;
    case Color::GREY:           return RGB(150, 150, 150);  break;
    case Color::BLUE:           return RGB(0,   0,   255);  break;
    case Color::GREEN:          return RGB(0,   255, 0  );  break;
    case Color::CYAN:           return RGB(0,   255, 255);  break;
    case Color::RED:            return RGB(255, 0,   0  );  break;
    case Color::MAGENTA:        return RGB(255, 0,   255);  break;
    case Color::YELLOW:         return RGB(255, 255, 0  );  break;
    case Color::WHITE:          return RGB(255, 255, 255);  break;
    default:
        return RGB(0, 0, 0);
    }
}

SCE_END
