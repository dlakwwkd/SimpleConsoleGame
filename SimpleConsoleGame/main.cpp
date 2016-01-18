#include "stdafx.h"
#include "GameManager.h"
#include "AssertPack.h"

int main()
{
    auto GM = GameManager::GetInstance();
    GM->Run();
    return 0;
}
