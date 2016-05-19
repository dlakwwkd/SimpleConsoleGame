#include "stdafx.h"
#include "GameManager.h"
#include "GameBase.h"
#include "Core/Console/Console.h"
#include "Core/Timer/Timer.h"
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
    static auto& scheduler = Scheduler::GetInstance();
    while (m_IsPlay)
    {
        scheduler.DoTask();

        m_Timer->Tick();
        float dt = m_Timer->DeltaTime();

        m_Game->Update(dt);
        if (m_Game->RenderLimitCheck(dt))
        {
            m_Game->Render();
        }
    }
    scheduler.Release();
}


SCE_END
