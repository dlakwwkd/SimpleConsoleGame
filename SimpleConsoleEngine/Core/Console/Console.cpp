#include "stdafx.h"
#include "Console.h"
SCE_START


Console::Console()
:   m_ScreenIndex(0),
    m_ScreenSize({ 0,0 })
{
}


Console::~Console()
{
    Release();
}

void Console::Init(const Coord& screenSize)
{
    std::ostringstream oss;
    oss << "mode con: lines=" << screenSize.m_Y << " cols=" << screenSize.m_X;
    system(oss.str().c_str());
    m_ScreenSize = screenSize;

    Release();
    m_ScreenBuffer[0] = CreateConsoleScreenBuffer(GENERIC_READ | GENERIC_WRITE, 0, NULL, CONSOLE_TEXTMODE_BUFFER, NULL);
    m_ScreenBuffer[1] = CreateConsoleScreenBuffer(GENERIC_READ | GENERIC_WRITE, 0, NULL, CONSOLE_TEXTMODE_BUFFER, NULL);
    
    CONSOLE_CURSOR_INFO cci;
    cci.dwSize = 1;
    cci.bVisible = FALSE;
    SetConsoleCursorInfo(m_ScreenBuffer[0], &cci);
    SetConsoleCursorInfo(m_ScreenBuffer[1], &cci);
}

void Console::Release()
{
    if (m_ScreenBuffer[0]) CloseHandle(m_ScreenBuffer[0]);
    if (m_ScreenBuffer[1]) CloseHandle(m_ScreenBuffer[1]);
}

SCE_END
