SCE_START


inline void Console::PrintText(const Coord& pos, const std::wstring& text) noexcept
{
    DWORD dw;
    SetConsoleCursorPosition(m_ScreenBuffer[m_ScreenIndex], { pos.m_X, pos.m_Y });
    WriteConsole(m_ScreenBuffer[m_ScreenIndex], text.c_str(), static_cast<DWORD>(text.length()), &dw, nullptr);
    ++m_DrawCall;
}

inline void Console::Print(const Coord& pos, wchar_t word) noexcept
{
    DWORD dw;
    SetConsoleCursorPosition(m_ScreenBuffer[m_ScreenIndex], { pos.m_X, pos.m_Y });
    WriteConsole(m_ScreenBuffer[m_ScreenIndex], &word, 1U, &dw, nullptr);
    ++m_DrawCall;
}

inline void Console::SetColor(Color textColor, Color bgColor) const noexcept
{
    WORD color = static_cast<WORD>(textColor) + (static_cast<WORD>(bgColor) << 4);
    SetConsoleTextAttribute(m_ScreenBuffer[m_ScreenIndex], color);
}

inline void Console::Clear() noexcept
{
    DWORD dw;
    DWORD screenSize = (m_ScreenSize.m_X + 2) * (m_ScreenSize.m_Y + 2);
    FillConsoleOutputCharacter(m_ScreenBuffer[m_ScreenIndex], L' ', screenSize, { 0,0 }, &dw);
    FillConsoleOutputAttribute(m_ScreenBuffer[m_ScreenIndex], NULL, screenSize, { 0,0 }, &dw);

    ZeroMemory(m_DepthBuffer, sizeof(m_DepthBuffer[0][0]) * MAX_CONSOLE_SIZE.m_X * MAX_CONSOLE_SIZE.m_Y);
}

inline void Console::SwapBuffer() noexcept
{
    SetConsoleActiveScreenBuffer(m_ScreenBuffer[m_ScreenIndex]);
    m_ScreenIndex = !m_ScreenIndex;
    m_DrawCall = 0;
}

inline bool Console::DepthCheck(const Coord& pos, BYTE depth) noexcept
{
    if (pos.m_X < 0 || pos.m_X > m_ScreenSize.m_X ||
        pos.m_Y < 0 || pos.m_Y > m_ScreenSize.m_Y ||
        m_DepthBuffer[pos.m_Y][pos.m_X] > depth)
    {
        return false;
    }
    m_DepthBuffer[pos.m_Y][pos.m_X] = depth + 1;
    return true;
}

SCE_END
