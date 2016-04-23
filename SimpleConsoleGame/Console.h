#pragma once

const COORD DEF_CONSOLE_SIZE = { 135, 35 };


class Console
{
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
    static Console* GetInstance()
    {
        static Console instance;
        return &instance;
    }
    void Init(COORD screenSize = DEF_CONSOLE_SIZE);
    void Release();

    inline static Color DarkenColor(const Color& color);

    inline void Init(int width, int height);
    inline void Print(int x, int y, const std::wstring& text)           const;

    inline void Print(COORD pos, const std::wstring& text)              const;
    inline void SetColor(Color textColor, Color bgColor = Color::BLACK) const;
    inline void Clear()                                                 const;
    inline void SwapBuffer();

private:
    HANDLE  m_ScreenBuffer[2];
    int     m_ScreenIndex;
    COORD   m_ScreenSize;

private:
    Console();
    ~Console();
};

inline Console::Color& operator++(Console::Color& color);

#include "Console.inl"
