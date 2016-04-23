#include "stdafx.h"
#include "GameManager.h"
#include "Console.h"
#include "Timer.h"
#include "Menu.h"
#include "GameA.h"


GameManager::GameManager() : m_Timer(nullptr), m_IsRun(false), m_IsPlay(false)
{
}


GameManager::~GameManager()
{
    Release();
}

void GameManager::Run()
{
    if (m_IsRun)
    {
        return;
    }
    Init();
    MainLoop();
    Release();
}



void GameManager::Init()
{
    Console::GetInstance()->Init();
    m_Timer = std::make_unique<Timer>();
    m_GameList = 
    {
        std::make_shared<GameA>(),
        std::make_shared<GameA>()
    };
    m_IsRun = true;
    m_IsPlay = false;
}

void GameManager::Release()
{
    m_IsPlay = false;
    m_IsRun = false;
    m_GameList.clear();
    m_Timer.reset();
    Console::GetInstance()->Release();
}



void GameManager::MainLoop()
{
    while (m_IsRun)
    {
        GameSelect();
        PlayGame();
    }
}

void GameManager::GameLoop()
{
    while (m_IsPlay)
    {
        m_Timer->Tick();
        m_CurGame->Update(m_Timer->DeltaTime());
        m_CurGame->Render();
    }
}



void GameManager::GameSelect()
{



    m_CurGame = m_GameList[0];
}

void GameManager::PlayGame()
{
    if (m_IsPlay || !m_CurGame)
    {
        return;
    }
    m_IsPlay = true;
    m_Timer->Init();
    m_CurGame->Init();

    GameLoop();

    m_CurGame->Release();
    m_CurGame.reset();
}
