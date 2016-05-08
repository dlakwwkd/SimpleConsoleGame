#include "stdafx.h"
#include "Core/Console/Console.h"
#include "Core/Game/GameManager.h"
#include "Game.h"
#include "Unit.h"
SCE_USE


Game::Game()
{
}


Game::~Game()
{
}

void Game::Init()
{
    m_Unit = Safe::New<Unit>();
}

void Game::Release()
{
    Safe::Delete(m_Unit);
}



void Game::Update(float dt)
{
    static float limit = 0.5f;
    static float stack = 0.0f;
    stack += dt;
    if (stack < limit)
        return;
    stack = 0.0f;

    static int s_X = 0;
    static int s_Y = 0;
    static Color s_Color = Color::BLUE;
    if (++s_X >= DEF_CONSOLE_SIZE.m_X)  s_X = 0;
    if (++s_Y >= DEF_CONSOLE_SIZE.m_Y)  s_Y = 0;
    ++s_Color;

    m_Unit->SetPos({ s_X, s_Y });
    m_Unit->SetShape(Shape(std::to_wstring(s_X).front(), s_Color, ::DarkenColor(s_Color)));
    m_Unit->Update(dt);
}

void Game::Render()
{
    auto& console = Console::GetInstance();
    console.Clear();

    m_Unit->Render();

    console.SwapBuffer();
}
