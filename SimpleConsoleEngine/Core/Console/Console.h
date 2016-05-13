﻿#pragma once
#include "Color.hpp"
#include "Coord.hpp"
SCE_START

constexpr Coord DEF_CONSOLE_SIZE = { 150, 50 };
constexpr Coord MAX_CONSOLE_SIZE = { 238, 70 };


class SCE_API Console
{
    CREATE_SINGLETON(Console)
public:
    void Init(const Coord& screenSize = DEF_CONSOLE_SIZE);
    void Release();

    inline void     Print(const Coord& pos, const std::wstring& text) noexcept;
    inline void     Print(const Coord& pos, const wchar_t& word) noexcept;
    inline void     SetColor(Color textColor, Color bgColor = Color::BLACK) const noexcept;
    inline void     Clear() const noexcept;
    inline void     SwapBuffer() noexcept;
    inline size_t   GetDrawCallNum() const noexcept { return m_DrawCall; }

private:
    HANDLE  m_ScreenBuffer[2];
    BYTE    m_ScreenIndex;
    Coord   m_ScreenSize;
    size_t  m_DrawCall;
};


SCE_END
#include "Console.inl"
