#include "AssertPack.h"

inline Color Console::DarkenColor(Color color)
{
    return color > 7 ? Color(color - 8) : color;
}



inline void Console::Init(int x, int y)
{
    Init({ Safe::IntegralCast<SHORT>(x), Safe::IntegralCast<SHORT>(y) });
}

inline void Console::Print(int x, int y, const std::wstring& text) const
{
    Print({ Safe::IntegralCast<SHORT>(x), Safe::IntegralCast<SHORT>(y) }, text);
}



inline void Console::Print(COORD pos, const std::wstring& text) const
{
    DWORD dw;
    SetConsoleCursorPosition(m_ScreenBuffer[m_ScreenIndex], pos);
    WriteConsole(m_ScreenBuffer[m_ScreenIndex], text.c_str(), static_cast<DWORD>(text.length()), &dw, NULL);
}

inline void Console::SetColor(Color textColor, Color bgColor) const
{
    WORD color = static_cast<WORD>(textColor) + (static_cast<WORD>(bgColor) << 4);
    SetConsoleTextAttribute(m_ScreenBuffer[m_ScreenIndex], color);
}

inline void Console::Clear() const
{
    DWORD dw;
    DWORD screenSize = m_ScreenSize.X * m_ScreenSize.Y;
    FillConsoleOutputCharacter(m_ScreenBuffer[m_ScreenIndex], L' ', screenSize, { 0,0 }, &dw);
    FillConsoleOutputAttribute(m_ScreenBuffer[m_ScreenIndex], NULL, screenSize, { 0,0 }, &dw);
}

inline void Console::SwapBuffer()
{
    SetConsoleActiveScreenBuffer(m_ScreenBuffer[m_ScreenIndex]);
    m_ScreenIndex = !m_ScreenIndex;
}
