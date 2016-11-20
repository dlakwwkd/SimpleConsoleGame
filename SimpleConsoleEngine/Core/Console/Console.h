#pragma once
#include "Color.hpp"
#include "Coord.h"
SCE_START

constexpr Coord MAX_CONSOLE_SIZE = { 238, 70 };


class Console
{
    CREATE_SINGLETON_NOEXCEPT(Console)
public:
    void    Init() noexcept;
    void    Release() noexcept;

    size_t  GetDrawCallNum() const noexcept;
    Coord   GetScreenSize() const noexcept;
    short   GetScreenWidth() const noexcept;
    short   GetScreenHeight() const noexcept;

    void    PrintText(const Coord& pos, const std::wstring& text) noexcept;
    void    Print(const Coord& pos, wchar_t word) noexcept;
    void    SetColor(Color textColor, Color bgColor = Color::BLACK) const noexcept;
    void    Clear() noexcept;
    void    SwapBuffer() noexcept;
    bool    DepthCheck(const Coord& pos, BYTE depth = 0) noexcept;

private:
    void    SetScreenAndFontSizeForThisDesktop(OUT SHORT& fontSize) noexcept;

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
