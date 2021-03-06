﻿#include "stdafx.h"

#define _CRTDBG_MAP_ALLOC
#include <crtdbg.h>

#include "Core/Game/GameManager.h"
#include "Game/Game.h"
#pragma comment(lib, "SimpleConsoleEngine.lib")

int main()
{
    _CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);
    SCE::GameManager::GetInstance().Run<Game>();
    return 0;
}
