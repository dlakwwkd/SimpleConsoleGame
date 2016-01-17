#include "stdafx.h"
#include "GameManager.h"
#include "AssertPack.h"

int main()
{
//     /* 테스트 코드 */
//     Assert::OverflowCheck<long>(MAXLONG);
//     Assert::OverflowCheck<int>(MAXINT);
//     Assert::OverflowCheck<short>(MAXSHORT);
//     Assert::OverflowCheck<char>(MAXCHAR);
//     Assert::OverflowCheck<short>(MAXSHORT + 1);
//     Assert::OverflowCheck<char>(MAXSHORT);
//     Assert::OverflowCheck<short>(-1);
//     Assert::OverflowCheck<short>((short)-10);

    auto GM = GameManager::GetInstance();
    GM->Run();
    return 0;
}
