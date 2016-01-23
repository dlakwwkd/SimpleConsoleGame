#pragma once
#include "Color.hpp"

const COORD DEF_CONSOLE_SIZE = { 135, 35 };


class Console
{
public:
    static Console* GetInstance()
    {
        static Console instance;
        return &instance;
    }
    void Init(COORD screenSize = DEF_CONSOLE_SIZE);
    void Release();

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
#include "Console.inl"
