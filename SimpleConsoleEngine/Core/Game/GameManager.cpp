#include "stdafx.h"
#include "GameManager.h"
#include "Scheduler.h"
#include "Interface/IGameBase.h"
#include "../Core/Timer/Timer.h"
#include "../Core/Console/Console.h"
SCE_START


GameManager::GameManager()
:   m_IsRun(false),
    m_IsPlay(false),
    m_FrameCount(0),
    m_RenderCount(0),
    m_RenderLimit(0)
{
}


GameManager::~GameManager()
{
}


void GameManager::ReturnMain()
{
    m_IsPlay = false;
}

void GameManager::Shutdown()
{
    m_IsRun = m_IsPlay = false;
}



void GameManager::Init()
{
    Console::GetInstance().Init();
    m_Scheduler = std::make_unique<Scheduler>();
    m_Timer = std::make_unique<Timer>();
    if (m_Scheduler && m_Timer)
    {
        m_IsRun = true;
    }
    else
    {
        m_IsRun = false;
    }
    m_IsPlay = false;
    m_FrameCount = 0;
    m_RenderCount = 0;
    m_RenderLimit = 0;
}

void GameManager::Release()
{
    m_IsPlay = false;
    m_IsRun = false;
    m_Timer.reset();
    m_Scheduler.reset();
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
    SetRenderLimit(60);
    while (m_IsPlay)
    {
        m_Scheduler->DoTask();
        UpdateProcess();
        if (RenderLimitCheck())
        {
            RenderProcess();
        }
    }
    m_Scheduler->Release();
}



void GameManager::UpdateProcess()
{
    float dt = FrameProgress();
    m_Game->Update(dt);
}

void GameManager::RenderProcess()
{
    static auto& console = Console::GetInstance();
    console.Clear();

    m_Game->Render();

    PrintFrame();
    console.SwapBuffer();
}



float GameManager::FrameProgress()
{
    ++m_FrameCount;
    m_Timer->Tick();
    return m_Timer->DeltaTime();
}

void GameManager::SetRenderLimit(size_t limitFrame)
{
    m_RenderLimit = limitFrame;
    m_Timer->SetDuration(1.0f / limitFrame);
}

bool GameManager::RenderLimitCheck()
{
    m_Timer->AccumDt();
    if (m_Timer->DurationCheck())
    {
        ++m_RenderCount;
        return true;
    }
    return false;
}

void GameManager::PrintFrame()
{
    static auto& console = Console::GetInstance();
    static size_t frameRate = 0;
    static size_t renderRate = 0;
    static Timer timer(1.f);
    timer.Tick();
    timer.AccumDt();
    if (timer.DurationCheck())
    {
        frameRate = m_FrameCount;
        renderRate = m_RenderCount;
        m_FrameCount = 0;
        m_RenderCount = 0;
    }
    std::wostringstream oss;
    oss << L"UpdateFrame: " << frameRate << L"\t"
        << L"RenderFrame: " << renderRate << L"/" << m_RenderLimit << L"\t"
        << L"DrawCall: " << console.GetDrawCallNum();
    console.SetColor(Color::WHITE);
    console.PrintText(Coord(0, console.GetScreenHeight() + 1), oss.str().c_str());
}

SCE_END
