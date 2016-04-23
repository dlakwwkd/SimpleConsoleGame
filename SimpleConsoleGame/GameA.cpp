#include "stdafx.h"
#include "GameA.h"
#include "Console.h"
#include "GameManager.h"

static Console::Color   g_Color = Console::Color::BLUE;
static int              g_X = 0;
static int              g_Y = 0;


GameA::GameA()
{
    m_GameName = L"GameA";
}


GameA::~GameA()
{
}

void GameA::Init()
{
}

void GameA::Release()
{
}



void GameA::Update(float dt)
{
    static float limit = 0.5f;
    static float stack = 0.0f;
    stack += dt;
    if (stack < limit)
        return;
    stack = 0.0f;

    if (++g_X >= DEF_CONSOLE_SIZE.X)    g_X = 0;
    if (++g_Y >= DEF_CONSOLE_SIZE.Y)    g_Y = 0;
    ++g_Color;
}

void GameA::Render()
{
    auto console = Console::GetInstance();
    console->Clear();

    console->SetColor(g_Color, Console::DarkenColor(g_Color));
    console->Print(g_X, g_Y, std::to_wstring(g_X));

    console->SwapBuffer();
}
