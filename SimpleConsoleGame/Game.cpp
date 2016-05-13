﻿#include "stdafx.h"
#include "Game.h"
#include "Unit.h"
#include "Hero.h"
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
    SetRenderLimitFrame(60);

    m_Command = std::make_unique<Command>();
    m_Hero = std::make_unique<Hero>();
    m_MobList.resize(100);
}

void Game::Release()
{
    m_MobList.clear();
    m_Hero.reset();
    m_Command.reset();
}



void Game::Update(float dt)
{
    FrameCalc(dt);
    CommandProc(dt);

    for (auto& mob : m_MobList)
    {
        mob.AI(dt);
        mob.Update(dt);
    }
    m_Hero->Update(dt);
}

void Game::Render()
{
    auto& console = Console::GetInstance();
    console.Clear();

    for (auto& mob : m_MobList)
    {
        mob.Render();
    }
    m_Hero->Render();

    FrameShow();
    console.SwapBuffer();
}



void Game::CommandProc(float dt)
{
    if (m_Command->IsKeyPress(Command::ESC))
    {
        GameManager::GetInstance().Shutdown();
        return;
    }
    if (m_Command->IsKeyPress(Command::UP))
    {
        m_Hero->AddMovePower(Vec2(0.0f, -dt));
    }
    if (m_Command->IsKeyPress(Command::DOWN))
    {
        m_Hero->AddMovePower(Vec2(0.0f, +dt));
    }
    if (m_Command->IsKeyPress(Command::LEFT))
    {
        m_Hero->AddMovePower(Vec2(-dt, 0.0f));
    }
    if (m_Command->IsKeyPress(Command::RIGHT))
    {
        m_Hero->AddMovePower(Vec2(+dt, 0.0f));
    }
}

void Game::FrameShow()
{
    auto& console = Console::GetInstance();

    std::wostringstream oss;
    oss << L"UpdateFrame: " << m_FrameRate << L"\n"
        << L"RenderFrame: " << m_RenderCount << L"/" << m_RenderRate << L"\n"
        << L"DrawCall: " << console.GetDrawCallNum();

    console.SetColor(Color::WHITE);
    console.PrintText(Coord(0, 0), oss.str().c_str());
}
