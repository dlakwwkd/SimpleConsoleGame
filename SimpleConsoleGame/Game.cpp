﻿#include "stdafx.h"
#include "Game.h"
#include "Unit.h"
#include "Mob.h"
#include "Dummy.h"
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
    srand((unsigned int)time(NULL));

    m_Command = std::make_unique<Command>();
    m_Unit = std::make_unique<Unit>();
    m_MobList.resize(10);
    for (auto& mob : m_MobList)
    {
        mob.Init();
    }
}

void Game::Release()
{
    m_MobList.clear();
    m_Unit.reset();
    m_Command.reset();
}



void Game::Update(float dt)
{
    static float accumDt = 0.0f;
    ++m_FrameCount;
    accumDt += dt;
    if (accumDt > 1.0f)
    {
        m_FrameRate = m_FrameCount;
        m_FrameCount = 0;
        accumDt = 0.0f;
    }
    CommandProc(dt);

    m_Unit->Update(dt);
    for (auto& mob : m_MobList)
    {
        mob.AI();
        mob.Update(dt);
    }

    static Color color = Color::GREY;
    static Color bgColor = Color::BLACK;

    static float limit1 = 0.1f;
    static float stack1 = 0.0f;
    stack1 += dt;
    if (stack1 > limit1)
    {
        m_Unit->SetShape(Shape(L'▣', ++color, bgColor));
        stack1 = 0.0f;
    }
    static float limit2 = 0.5f;
    static float stack2 = 0.0f;
    stack2 += dt;
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

    for (auto& mob : m_MobList)
    {
        mob.Render();
    }
    m_Unit->Render();

    console.SetColor(Color::WHITE);
    console.Print(Coord(0, 0), std::to_wstring(m_FrameRate));
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
