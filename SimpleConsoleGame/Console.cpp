#include "stdafx.h"
#include "Console.h"


Console::Console() : m_ScreenIndex(0), m_ScreenSize({ 0,0 })
{
}


Console::~Console()
{
    Release();
}

void Console::Init(COORD screenSize)
{
    std::ostringstream oss;
    oss << "mode con: lines=" << screenSize.Y << " cols=" << screenSize.X;
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



void Console::Print(COORD pos, const std::wstring& text) const
{
    DWORD dw;
    SetConsoleCursorPosition(m_ScreenBuffer[m_ScreenIndex], pos);
    WriteConsole(m_ScreenBuffer[m_ScreenIndex], text.c_str(), text.length(), &dw, NULL);
}

void Console::SetColor(Color textColor, Color bgColor) const
{
    WORD color = textColor + bgColor * 16;
    SetConsoleTextAttribute(m_ScreenBuffer[m_ScreenIndex], color);
}

void Console::Clear() const
{
    DWORD dw;
    DWORD screenSize = m_ScreenSize.X * m_ScreenSize.Y;
    FillConsoleOutputCharacter(m_ScreenBuffer[m_ScreenIndex], L' ', screenSize, { 0,0 }, &dw);
    FillConsoleOutputAttribute(m_ScreenBuffer[m_ScreenIndex], NULL, screenSize, { 0,0 }, &dw);
}

void Console::SwapBuffer()
{
    SetConsoleActiveScreenBuffer(m_ScreenBuffer[m_ScreenIndex]);
    m_ScreenIndex = !m_ScreenIndex;
}
