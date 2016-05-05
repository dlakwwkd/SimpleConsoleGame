#pragma once
SCE_START

const COORD DEF_CONSOLE_SIZE = { 135, 35 };


class SCE_API Console
{
    CREATE_SINGLETON(Console)
public:
    enum class Color : WORD
    {
        BLACK = 0,

        DARK_BLUE,
        DARK_GREEN,
        DARK_CYAN,
        DARK_RED,
        DARK_MAGENTA,
        DARK_YELLOW,
        DARK_WHITE,

        GREY,

        BLUE,
        GREEN,
        CYAN,
        RED,
        MAGENTA,
        YELLOW,
        WHITE,
    };
public:
    void Init(COORD screenSize = DEF_CONSOLE_SIZE);
    void Release();

    inline void Init(int width, int height);
    inline void Print(int x, int y, const std::wstring& text) const noexcept;
    inline void Print(COORD pos, const std::wstring& text) const noexcept;
    inline void SetColor(Color textColor, Color bgColor = Color::BLACK) const noexcept;
    inline void Clear() const noexcept;
    inline void SwapBuffer() noexcept;

    inline static Color DarkenColor(const Color& color) noexcept;

private:
    HANDLE  m_ScreenBuffer[2];
    int     m_ScreenIndex;
    COORD   m_ScreenSize;
};

inline Console::Color& operator++(Console::Color& color) noexcept;

SCE_END
#include "Console.inl"
