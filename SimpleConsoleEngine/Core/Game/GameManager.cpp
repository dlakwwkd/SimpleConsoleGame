#include "stdafx.h"
#include "GameManager.h"
#include "IGame.h"
#include "../Timer/Timer.h"
#include "../Console/Console.h"
#include "../../Util/AssertPack.h"
SCE_START


GameManager::GameManager()
:   m_Game(nullptr),
    m_Timer(nullptr),
    m_IsRun(false),
    m_IsPlay(false)
{
}


GameManager::~GameManager()
{
    Safe::Delete(m_Timer);
    Safe::Delete(m_Game);
}

void GameManager::Init()
{
    Console::GetInstance().Init();
    m_Timer = Safe::New<Timer>();
    m_IsRun = m_Timer ? true : false;
    m_IsPlay = false;
}

void GameManager::Release()
{
    m_IsPlay = false;
    m_IsRun = false;
    Safe::Delete(m_Timer);
    Console::GetInstance().Release();

    Safe::Delete(m_Game);
}

void GameManager::MainLoop()
{
    while (m_IsRun)
    {
        if (!m_Timer || !m_Game)
        {
            assert(false);
            return;
        }
        m_IsPlay = true;
        m_Timer->Init();
        m_Game->Init();
        GameLoop();
        m_Game->Release();
    }
}

void GameManager::GameLoop()
{
    while (m_IsPlay)
    {
        m_Timer->Tick();
        m_Game->Update(m_Timer->DeltaTime());
        m_Game->Render();
    }
}


SCE_END
