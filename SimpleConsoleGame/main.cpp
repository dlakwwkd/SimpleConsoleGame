#include "stdafx.h"
#include "Console.h"

int main()
{
//     /* 테스트 코드 */
//     Assert::OverflowCheck(MAXLONG, TYPE(long));
//     Assert::OverflowCheck(MAXINT, TYPE(int));
//     Assert::OverflowCheck(MAXSHORT, TYPE(short));
//     Assert::OverflowCheck(MAXCHAR, TYPE(char));
//     Assert::OverflowCheck(MAXSHORT + 1, TYPE(short));
//     Assert::OverflowCheck(MAXSHORT, TYPE(char));
//     Assert::OverflowCheck(-1, TYPE(short));
//     Assert::OverflowCheck((short)-10, TYPE(short));

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
