#include "stdafx.h"
#include "GameManager.h"
#include "Console.h"
#include "Timer.h"

static Color    g_Color = BLUE;
static int      g_X     = 0;
static int      g_Y     = 0;

GameManager::GameManager() : m_Timer(nullptr), m_IsGameRun(false)
{
}


GameManager::~GameManager()
{
    Release();
}

void GameManager::Init()
{
    Console::GetInstance()->Init(COLS, LINES);
    m_Timer = std::make_unique<Timer>();
    m_IsGameRun = true;
}

void GameManager::Release()
{
    Console::GetInstance()->Release();
}



void GameManager::Run()
{
    Init();
    GameLoop();
    Release();
}

void GameManager::GameLoop()
{
    m_Timer->Init();
    while (m_IsGameRun)
    {
        m_Timer->Tick();
        Update(m_Timer->DeltaTime());
        Render();
    }
}



void GameManager::Update(float dt)
{
    static float limit = 0.5f;
    static float stack = 0.0f;
    stack += dt;
    if (stack < limit)
        return;
    stack = 0.0f;

    g_Color = Color(g_Color + 1);
    if (g_Color > WHITE)  g_Color = BLUE;
    if (++g_X >= COLS)    g_X = 0;
    if (++g_Y >= LINES)   g_Y = 0;
}

void GameManager::Render()
{
    auto console = Console::GetInstance();
    console->Clear();

    console->SetColor(g_Color, Console::DarkenColor(g_Color));
    console->Print(g_X, g_Y, std::to_wstring(g_X));

    console->SwapBuffer();
}
