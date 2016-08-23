﻿#include "stdafx.h"
#include "Game.h"
//----------------------------------------------------------------------------------------------------
#include "SimpleConsoleEngine/Core/Timer/Timer.h"
#include "SimpleConsoleEngine/Core/Command/Command.h"
#include "SimpleConsoleEngine/Core/Console/Console.h"
#include "SimpleConsoleEngine/Core/Game/GameManager.h"
#include "SimpleConsoleEngine/Core/Game/Component/CmdRenderComponent.h"
//----------------------------------------------------------------------------------------------------
#include "GameObject/Dummy.h"
#include "GameObject/Unit.h"
#include "GameObject/Unit/Hero.h"
#include "GameObject/Unit/Mob.h"
#include "GameObject/Unit/Missile.h"
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
    m_Hero = std::make_unique<Hero>();

    size_t mobNum = 30;
    size_t section = mobNum / 5;
    m_MobList.resize(mobNum);
    for (size_t i = 0; i < mobNum; ++i)
    {
        auto& mob = m_MobList[i];
        auto render = mob.GetComponent<CmdRenderComponent>();
        if (render == nullptr)
            continue;

        if (i < section)
        {
            render->SetShape(Shape(L'☠', Color::GREY));
            mob.SetSpeed(120.0f);
            mob.SetAIRatio(0.5f);
        }
        else if (i < section * 2)
        {
            render->SetShape(Shape(L'☣', Color::RED));
            mob.SetSpeed(70.0f);
            mob.SetAIRatio(1.0f);
        }
        else if (i < section * 3)
        {
            render->SetShape(Shape(L'☯', Color::GREEN));
            mob.SetSpeed(30.0f);
            mob.SetAIRatio(1.5f);
        }
        else if (i < section * 4)
        {
            render->SetShape(Shape(L'♋', Color::CYAN));
            mob.SetSpeed(30.0f);
            mob.SetAIRatio(1.5f);
        }
        else
        {
            render->SetShape(Shape(L'★', Color::YELLOW));
            mob.SetSpeed(10.0f);
            mob.SetAIRatio(2.0f);
        }
    }

    /*
    // 테스트 용 코드
    auto& gm = GameManager::GetInstance();
    gm.CallFuncAfterM(8.0f, &gm, &GameManager::ReturnMain);     // 게임 초기화
    gm.CallFuncAfterM(2.0f, this, &Game::CommandProc, 10.0f);   // 순간가속
    gm.CallFuncAfterS(4.0f,                                     // 순간정지
        [](auto&& moblist)
        {
            for (size_t i = 0; i < moblist.size(); ++i)
            {
                Sleep(50);
            }
        },
        m_MobList);
    */
}

void Game::Release()
{
    m_MobList.clear();
    m_Hero.reset();
    m_Command.reset();
}



void Game::Update(float dt)
{
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
    for (auto& mob : m_MobList)
    {
        mob.Render();
    }
    m_Hero->Render();
}



void Game::CommandProc(float dt)
{
    if (m_Command->IsKeyPress<Command::ESC>())
    {
        GameManager::GetInstance().Shutdown();
        return;
    }
    if (m_Command->IsKeyPress<Command::UP>())
    {
        m_Hero->AddMovePower(Vec2::UP * dt);
    }
    if (m_Command->IsKeyPress<Command::DOWN>())
    {
        m_Hero->AddMovePower(Vec2::DOWN * dt);
    }
    if (m_Command->IsKeyPress<Command::LEFT>())
    {
        m_Hero->AddMovePower(Vec2::LEFT * dt);
    }
    if (m_Command->IsKeyPress<Command::RIGHT>())
    {
        m_Hero->AddMovePower(Vec2::RIGHT * dt);
    }
    if (m_Command->IsKeyPress<Command::BUTTON_A>())
    {
    }
}
