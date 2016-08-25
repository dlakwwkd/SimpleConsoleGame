#pragma once
#include "Color.hpp"
#include "Coord.h"
SCE_START

constexpr Coord DEF_CONSOLE_SIZE = { 130, 35 };
constexpr Coord MAX_CONSOLE_SIZE = { 238, 70 };


class Console
{
    CREATE_SINGLETON(Console)
public:
    void    Init(const Coord& screenSize = DEF_CONSOLE_SIZE);
    void    Release();

    size_t  GetDrawCallNum() const;
    Coord   GetScreenSize() const;
    short   GetScreenWidth() const;
    short   GetScreenHeight() const;

    void    PrintText(const Coord& pos, const std::wstring& text);
    void    Print(const Coord& pos, wchar_t word);
    void    SetColor(Color textColor, Color bgColor = Color::BLACK) const;
    void    Clear();
    void    SwapBuffer();
    bool    DepthCheck(const Coord& pos, BYTE depth = 0);

private:
    CONSOLE_FONT_INFOEX m_CFIOrigin;
    HANDLE              m_STDHandle;

    HANDLE              m_ScreenBuffer[2];
    BYTE                m_ScreenIndex;
    Coord               m_ScreenSize;
    size_t              m_DrawCall;

    BYTE                m_DepthBuffer[MAX_CONSOLE_SIZE.m_Y][MAX_CONSOLE_SIZE.m_X];
};

SCE_END
