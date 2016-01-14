#pragma once
enum DefaultConsoleSize
{
    LINES   = 35,
    COLS    = 135,
};
enum Color
{
    BLACK = 0,
    GREY = 8,
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

    void Print(COORD pos, const std::wstring& text)              const;
    void SetColor(Color textColor, Color bgColor = Color::BLACK) const;
    void Clear()                                                 const;
    void SwapBuffer();

    inline void         Init(int x, int y)                                  { Init({ static_cast<SHORT>(x), static_cast<SHORT>(y) }); }
    inline void         Print(int x, int y, const std::wstring& text) const { Print({ static_cast<SHORT>(x), static_cast<SHORT>(y) }, text); }
    inline static Color DarkenColor(Color color)                            { return color > 7 ? Color(color - 8) : color; }

private:
    Console();
    ~Console();

    HANDLE  m_ScreenBuffer[2];
    int     m_ScreenIndex;
    COORD   m_ScreenSize;
};

