#pragma once
#include "Color.hpp"
#include "Coord.hpp"
SCE_START

constexpr Coord DEF_CONSOLE_SIZE = { 130, 35 };
constexpr Coord MAX_CONSOLE_SIZE = { 238, 70 };


class SCE_API Console
{
    CREATE_SINGLETON(Console)
public:
    void Init(const Coord& screenSize = DEF_CONSOLE_SIZE);
    void Release();

    size_t  GetDrawCallNum() const noexcept { return m_DrawCall; }
    Coord   GetScreenSize() const noexcept { return m_ScreenSize; }
    short   GetScreenWidth() const noexcept { return m_ScreenSize.m_X; }
    short   GetScreenHeight() const noexcept { return m_ScreenSize.m_Y; }

    inline void PrintText(const Coord& pos, const std::wstring& text) noexcept;
    inline void Print(const Coord& pos, wchar_t word) noexcept;
    inline void SetColor(Color textColor, Color bgColor = Color::BLACK) const noexcept;
    inline void Clear() noexcept;
    inline void SwapBuffer() noexcept;
    inline bool DepthCheck(const Coord& pos, BYTE depth = 0) noexcept;

private:
    HANDLE  m_ScreenBuffer[2];
    BYTE    m_ScreenIndex;
    Coord   m_ScreenSize;
    size_t  m_DrawCall;

    BYTE    m_DepthBuffer[MAX_CONSOLE_SIZE.m_Y][MAX_CONSOLE_SIZE.m_X];
};

SCE_END
#include "Console.inl"
