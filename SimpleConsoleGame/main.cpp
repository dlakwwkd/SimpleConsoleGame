#include "stdafx.h"
#include "Core/Game/GameManager.h"
#include "Game.h"

int main()
{
    SCE::GameManager::GetInstance().Run<Game>();
    return 0;
}
