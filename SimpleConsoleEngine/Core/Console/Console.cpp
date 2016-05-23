#include "stdafx.h"
#include "Console.h"
SCE_START


Console::Console()
:   m_ScreenBuffer{ nullptr, nullptr },
    m_ScreenIndex(0),
    m_ScreenSize{ 0,0 },
    m_DrawCall(0),
    m_DepthBuffer{ {0} }
{
}


Console::~Console()
{
}

void Console::Init(const Coord& screenSize)
{
    Release();

    std::ostringstream oss;
    oss << "mode con: lines=" << screenSize.m_Y + 2 << " cols=" << screenSize.m_X + 2;
    system(oss.str().c_str());
    m_ScreenSize = screenSize;

    HWND hConsole = GetConsoleWindow();
    MoveWindow(hConsole, 0, 0, 0, 0, TRUE);

    SHORT fontSize;
    RECT desktopSize;
    HWND hDesktop = GetDesktopWindow();
    GetWindowRect(hDesktop, &desktopSize);
    if (desktopSize.bottom >= 1200)
        fontSize = 24;
    else if (desktopSize.bottom >= 900)
        fontSize = 20;
    else if (desktopSize.bottom >= 768)
        fontSize = 16;
    else
        fontSize = 14;

    m_STDHandle = GetStdHandle(STD_OUTPUT_HANDLE);

    CONSOLE_FONT_INFOEX cfi{ sizeof(cfi) };
    GetCurrentConsoleFontEx(m_STDHandle, FALSE, &cfi);
    CopyMemory(&m_CFIOrigin, &cfi, sizeof(cfi));
    CopyMemory(cfi.FaceName, L"굴림체", LF_FACESIZE);
    cfi.dwFontSize.Y = fontSize;

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

void Console::Release()
{
    if (m_ScreenBuffer[0]) CloseHandle(m_ScreenBuffer[0]);
    if (m_ScreenBuffer[1]) CloseHandle(m_ScreenBuffer[1]);
    SetCurrentConsoleFontEx(m_STDHandle, FALSE, &m_CFIOrigin);
}

SCE_END
