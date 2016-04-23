#include "AssertPack.h"

inline Console::Color& operator++(Console::Color& color)
{
    WORD idx = static_cast<WORD>(color);

    if (++idx == static_cast<WORD>(Console::Color::GREY))
    {
        color = Console::Color::BLACK;
    }
    else if (idx > static_cast<WORD>(Console::Color::WHITE))
    {
        color = Console::Color::GREY;
    }
    else
        color = static_cast<Console::Color>(idx);
    return color;
}



inline Console::Color Console::DarkenColor(const Color& color)
{
    WORD idx = static_cast<WORD>(color);
    WORD comp = static_cast<WORD>(Color::GREY);
    return idx < comp ? color : static_cast<Color>(idx - comp);
}



inline void Console::Init(int width, int height)
{
    Init({ Safe::IntegralCast<SHORT>(width), Safe::IntegralCast<SHORT>(height) });
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
