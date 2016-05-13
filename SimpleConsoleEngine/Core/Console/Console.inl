#include "../../Util/AssertPack.h"
SCE_START


inline void Console::Print(const Coord& pos, const std::wstring& text) noexcept
{
    DWORD dw;
    SetConsoleCursorPosition(m_ScreenBuffer[m_ScreenIndex], { pos.m_X, pos.m_Y });
    WriteConsole(m_ScreenBuffer[m_ScreenIndex], text.c_str(), static_cast<DWORD>(text.length()), &dw, nullptr);
    ++m_DrawCall;
}

inline void Console::Print(const Coord& pos, const wchar_t& word) noexcept
{
    DWORD dw;
    SetConsoleCursorPosition(m_ScreenBuffer[m_ScreenIndex], { pos.m_X, pos.m_Y });
    WriteConsole(m_ScreenBuffer[m_ScreenIndex], &word, 1U, &dw, nullptr);
    ++m_DrawCall;
}

inline void Console::SetColor(Color textColor, Color bgColor) const noexcept
{
    WORD&& color = static_cast<WORD>(textColor) + (static_cast<WORD>(bgColor) << 4);
    SetConsoleTextAttribute(m_ScreenBuffer[m_ScreenIndex], color);
}

inline void Console::Clear() const noexcept
{
    DWORD dw;
    DWORD screenSize = m_ScreenSize.m_X * m_ScreenSize.m_Y;
    FillConsoleOutputCharacter(m_ScreenBuffer[m_ScreenIndex], L' ', screenSize, { 0,0 }, &dw);
    FillConsoleOutputAttribute(m_ScreenBuffer[m_ScreenIndex], NULL, screenSize, { 0,0 }, &dw);
}

inline void Console::SwapBuffer() noexcept
{
    SetConsoleActiveScreenBuffer(m_ScreenBuffer[m_ScreenIndex]);
    m_ScreenIndex = !m_ScreenIndex;
    m_DrawCall = 0;
}

SCE_END
