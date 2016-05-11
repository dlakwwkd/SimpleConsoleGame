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
    m_Unit->Update(dt);

    static Color color = Color::GREY;
    static Color bgColor = Color::BLACK;


    static float limit1 = 0.1f;
    static float limit2 = 0.5f;
    static float stack1 = 0.0f;
    static float stack2 = 0.0f;
    stack1 += dt;
    stack2 += dt;
    if (stack1 > limit1)
    {
        m_Unit->SetShape(Shape(L'★', ++color, bgColor));
        stack1 = 0.0f;
    }
    if (stack2 > limit2)
    {
        //++bgColor;
        stack2 = 0.0f;
    }
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
    if (m_Command->IsKeyPress(Command::DOWN))
    {
        m_Unit->AddMovePower(Vec2(0.0f, +dt));
    }
    if (m_Command->IsKeyPress(Command::LEFT))
    {
        m_Unit->AddMovePower(Vec2(-dt, 0.0f));
    }
    if (m_Command->IsKeyPress(Command::RIGHT))
    {
        m_Unit->AddMovePower(Vec2(+dt, 0.0f));
    }
}
