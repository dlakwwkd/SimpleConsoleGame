#include "stdafx.h"
#include "Console.h"

int main()
{
//     /* 테스트 코드 */
//     Assert::OverflowCheck(MAXLONG,      Type<long>::value);
//     Assert::OverflowCheck(MAXINT,       Type<int>::value);
//     Assert::OverflowCheck(MAXSHORT,     Type<short>::value);
//     Assert::OverflowCheck(MAXCHAR,      Type<char>::value);
//     Assert::OverflowCheck(MAXSHORT + 1, Type<short>::value);
//     Assert::OverflowCheck(MAXSHORT,     Type<char>::value);
//     Assert::OverflowCheck(-1,           Type<short>::value);
//     Assert::OverflowCheck((short)-10,   Type<short>::value);

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
