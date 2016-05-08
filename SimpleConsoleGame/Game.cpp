#include "stdafx.h"
#include "Game.h"
#include "Core/Console/Console.h"
#include "Core/Game/GameManager.h"
SCE_USE


static Color    g_Color = Color::BLUE;
static int      g_X = 0;
static int      g_Y = 0;


Game::Game()
{
}


Game::~Game()
{
}

void Game::Init()
{
}

void Game::Release()
{
}



void Game::Update(float dt)
{
    static float limit = 0.5f;
    static float stack = 0.0f;
    stack += dt;
    if (stack < limit)
        return;
    stack = 0.0f;

    if (++g_X >= DEF_CONSOLE_SIZE.m_X)  g_X = 0;
    if (++g_Y >= DEF_CONSOLE_SIZE.m_Y)  g_Y = 0;
    ++g_Color;
}

void Game::Render()
{
    auto& console = Console::GetInstance();
    console.Clear();

    console.SetColor(g_Color, ::DarkenColor(g_Color));
    console.Print(g_X, g_Y, std::to_wstring(g_X));

    console.SwapBuffer();
}
