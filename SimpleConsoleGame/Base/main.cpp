#include "stdafx.h"

#define _CRTDBG_MAP_ALLOC
#include <crtdbg.h>

#include "Core/ObjectPool/ObjectPool.h"
#include "Core/Game/GameManager.h"
#include "Game/Game.h"
#pragma comment(lib, "SimpleConsoleEngine.lib")

int main()
{
    _CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);
    //_CrtSetBreakAlloc(158);

    SCE::GameManager::GetInstance().Run<Game>();
    SCE::_objectPoolDeleteHelper::DeleteAll();

    ::OutputDebugString(_T("Memory Leak Test!!!\n"));
    return 0;
}
