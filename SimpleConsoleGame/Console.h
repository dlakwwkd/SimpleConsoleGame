#pragma once
enum DefaultConsoleSize
{
    LINES   = 35,
    COLS    = 135,
};
enum Color
{
    BLACK   = 0,
    GREY    = 8,
    BLUE,
    GREEN,
    CYAN,
    RED,
    MAGENTA,
    YELLOW,
    WHITE,
};

class Console
{
public:
    static Console* GetInstance()
    {
        static Console instance;
        return &instance;
    }
    void Init(COORD screenSize);
    void Release();

    inline static Color DarkenColor(Color color);

    inline void         Init(int x, int y);
    inline void         Print(int x, int y, const std::wstring& text)           const;

    inline void         Print(COORD pos, const std::wstring& text)              const;
    inline void         SetColor(Color textColor, Color bgColor = Color::BLACK) const;
    inline void         Clear()                                                 const;
    inline void         SwapBuffer();
private:
    Console();
    ~Console();

    HANDLE  m_ScreenBuffer[2];
    int     m_ScreenIndex;
    COORD   m_ScreenSize;
};
#include "Console.inl"
