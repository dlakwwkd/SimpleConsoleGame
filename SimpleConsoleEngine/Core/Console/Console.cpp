#include "stdafx.h"
#include "Console.h"
SCE_START


Console::Console() noexcept
    : m_ScreenBuffer{ nullptr, nullptr }
    , m_ScreenIndex(0)
    , m_ScreenSize{ 0,0 }
    , m_DrawCall(0)
    , m_DepthBuffer{ {0} }
{
}


Console::~Console()
{
}

void Console::Init() noexcept
{
    Release();

    HWND hConsole = GetConsoleWindow();
    MoveWindow(hConsole, 0, 0, 0, 0, TRUE);

    m_STDHandle = GetStdHandle(STD_OUTPUT_HANDLE);

    CONSOLE_FONT_INFOEX cfi{ sizeof(cfi) };
    GetCurrentConsoleFontEx(m_STDHandle, FALSE, &cfi);
    CopyMemory(&m_CFIOrigin, &cfi, sizeof(cfi));
    CopyMemory(cfi.FaceName, L"굴림체", LF_FACESIZE);
    SetScreenAndFontSizeForThisDesktop(cfi.dwFontSize.Y);

    CONSOLE_CURSOR_INFO cci;
    cci.dwSize = 1;
    cci.bVisible = FALSE;

    for (size_t i = 0; i < 2; ++i)
    {
        auto& handle = m_ScreenBuffer[i];
        handle = CreateConsoleScreenBuffer(GENERIC_READ | GENERIC_WRITE, 0, NULL, CONSOLE_TEXTMODE_BUFFER, NULL);
        SetConsoleActiveScreenBuffer(handle);
        SetCurrentConsoleFontEx(handle, FALSE, &cfi);
        SetConsoleCursorInfo(handle, &cci);
    }
}

void Console::Release() noexcept
{
    if (m_ScreenBuffer[0]) CloseHandle(m_ScreenBuffer[0]);
    if (m_ScreenBuffer[1]) CloseHandle(m_ScreenBuffer[1]);
    SetCurrentConsoleFontEx(m_STDHandle, FALSE, &m_CFIOrigin);
}


size_t Console::GetDrawCallNum() const noexcept
{
    return m_DrawCall;
}

Coord Console::GetScreenSize() const noexcept
{
    return m_ScreenSize;
}

short Console::GetScreenWidth() const noexcept
{
    return m_ScreenSize.m_X;
}

short Console::GetScreenHeight() const noexcept
{
    return m_ScreenSize.m_Y;
}


void Console::PrintText(const Coord& pos, const std::wstring& text) noexcept
{
    DWORD dw;
    SetConsoleCursorPosition(m_ScreenBuffer[m_ScreenIndex], { pos.m_X, pos.m_Y });
    WriteConsole(m_ScreenBuffer[m_ScreenIndex], text.c_str(), static_cast<DWORD>(text.length()), &dw, nullptr);
    ++m_DrawCall;
}

void Console::Print(const Coord& pos, wchar_t word) noexcept
{
    DWORD dw;
    SetConsoleCursorPosition(m_ScreenBuffer[m_ScreenIndex], { pos.m_X, pos.m_Y });
    WriteConsole(m_ScreenBuffer[m_ScreenIndex], &word, 1U, &dw, nullptr);
    ++m_DrawCall;
}

void Console::SetColor(Color textColor, Color bgColor) const noexcept
{
    WORD color = static_cast<WORD>(textColor) + (static_cast<WORD>(bgColor) << 4);
    SetConsoleTextAttribute(m_ScreenBuffer[m_ScreenIndex], color);
}

void Console::Clear() noexcept
{
    DWORD dw;
    DWORD screenSize = (m_ScreenSize.m_X + 2) * (m_ScreenSize.m_Y + 2);
    FillConsoleOutputCharacter(m_ScreenBuffer[m_ScreenIndex], L' ', screenSize, { 0,0 }, &dw);
    FillConsoleOutputAttribute(m_ScreenBuffer[m_ScreenIndex], NULL, screenSize, { 0,0 }, &dw);

    ZeroMemory(m_DepthBuffer, sizeof(m_DepthBuffer[0][0]) * MAX_CONSOLE_SIZE.m_X * MAX_CONSOLE_SIZE.m_Y);
}

void Console::SwapBuffer() noexcept
{
    SetConsoleActiveScreenBuffer(m_ScreenBuffer[m_ScreenIndex]);
    m_ScreenIndex = !m_ScreenIndex;
    m_DrawCall = 0;
}

bool Console::DepthCheck(const Coord& pos, BYTE depth) noexcept
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


void Console::SetScreenAndFontSizeForThisDesktop(OUT SHORT& fontSize) noexcept
{
    RECT desktopSize;
    HWND hDesktop = GetDesktopWindow();
    GetWindowRect(hDesktop, &desktopSize);
    if (desktopSize.bottom > 1200)
    {
        m_ScreenSize = { 210, 63 };
        fontSize = 16;
    }
    else if (desktopSize.bottom > 900)
    {
        m_ScreenSize = { 200, 60 };
        fontSize = 16;
    }
    else if (desktopSize.bottom >= 768)
    {
        m_ScreenSize = { 158, 42 };
        fontSize = 14;
    }
    else
    {
        m_ScreenSize = { 150, 40 };
        fontSize = 14;
    }
    std::ostringstream oss;
    oss << "mode con: lines="   << m_ScreenSize.m_Y + 2
        << " cols="             << m_ScreenSize.m_X + 2;
    system(oss.str().c_str());
}

SCE_END
