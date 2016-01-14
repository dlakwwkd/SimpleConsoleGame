#include "stdafx.h"
#include "Console.h"

int main()
{
    auto console = Console::GetInstance();
    console->Init(COLS, LINES);

    while (true)
    {
        Sleep(100);
        console->Clear();

        static Color color = BLUE;
        static int x = 0;
        static int y = 0;
        
        color = Color(color + 1);
        if (color > WHITE)  color = BLUE;
        if (++x >= COLS)    x = 0;
        if (++y >= LINES)   y = 0;

        console->SetColor(color, Console::DarkenColor(color));
        console->Print(x, y, std::to_wstring(x));

        console->SwapBuffer();
    }
    console->Release();
    return 0;
}

