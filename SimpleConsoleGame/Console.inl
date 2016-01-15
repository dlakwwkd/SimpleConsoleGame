#include "AssertPack.h"

inline void Console::Init(int x, int y)
{
    Init({ Safe::IntegralCast(x, TYPE(SHORT)), Safe::IntegralCast(y, TYPE(SHORT)) });
}
inline void Console::Print(int x, int y, const std::wstring& text) const
{
    Print({ Safe::IntegralCast(x, TYPE(SHORT)), Safe::IntegralCast(y, TYPE(SHORT)) }, text);
}
inline Color Console::DarkenColor(Color color)
{
    return color > 7 ? Color(color - 8) : color;
}
