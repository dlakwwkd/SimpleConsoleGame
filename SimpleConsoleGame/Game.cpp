#include "stdafx.h"
#include "Game.h"
#include "Unit.h"
#include "Core/Game/GameManager.h"
#include "Core/Console/Console.h"
#include "Core/Command/Command.h"
SCE_USE


Game::Game()
{
}


Game::~Game()
{
}

void Game::Init()
{
    m_Command = std::make_unique<Command>();
    m_Unit = std::make_unique<Unit>();
}

void Game::Release()
{
    m_Unit.reset();
    m_Command.reset();
}



void Game::Update(float dt)
{
    CommandProc(dt);

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
    m_Unit->SetShape(Shape(std::to_wstring(s_X).back(), s_Color, ::DarkenColor(s_Color)));
    m_Unit->Update(dt);
}

void Game::Render()
{
    auto& console = Console::GetInstance();
    console.Clear();

    m_Unit->Render();

    console.SwapBuffer();
}



void Game::CommandProc(float dt)
{
    if (m_Command->IsKeyPress(Command::UP))
    {
        m_Unit->AddMovePower(Vec2(0.0f, -dt));
    }
}
