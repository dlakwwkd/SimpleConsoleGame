﻿#include "stdafx.h"
#include "Core/Game/GameManager.h"
#include "Game/Game.h"
#pragma comment(lib, "SimpleConsoleEngine.lib")

int main()
{
    SCE::GameManager::GetInstance().Run<Game>();
    return 0;
}
