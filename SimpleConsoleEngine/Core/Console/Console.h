#pragma once
#include "Color.hpp"
#include "Coord.hpp"
SCE_START

const Coord DEF_CONSOLE_SIZE = { 135, 35 };


class SCE_API Console
{
    CREATE_SINGLETON(Console)
public:
    void Init(const Coord& screenSize = DEF_CONSOLE_SIZE);
    void Release();

    inline void Init(int width, int height);
    inline void Print(int x, int y, const std::wstring& text) const noexcept;
    inline void Print(const Coord& pos, const std::wstring& text) const noexcept;
    inline void SetColor(Color textColor, Color bgColor = Color::BLACK) const noexcept;
    inline void Clear() const noexcept;
    inline void SwapBuffer() noexcept;

private:
    HANDLE  m_ScreenBuffer[2];
    BYTE    m_ScreenIndex;
    Coord   m_ScreenSize;
};


SCE_END
#include "Console.inl"
