#include "stdafx.h"
#include "Game.h"
//----------------------------------------------------------------------------------------------------
#include "Core/Timer/Timer.h"
#include "Core/Command/Command.h"
#include "Core/Console/Console.h"
#include "Core/Game/GameManager.h"
#include "Core/Game/Component/RenderComponent/CmdRenderComponent.h"
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
    m_Hero = std::make_shared<Hero>();

    size_t mobNum = 30;
    size_t section = mobNum / 5;
    for (size_t i = 0; i < mobNum; ++i)
    {
        m_MobList.emplace_back(std::make_shared<Mob>());
        auto& mob = m_MobList[i];
        auto render = mob->GetComponent<CmdRenderComponent>();
        if (render == nullptr)
            continue;

        if (i < section)
        {
            render->SetShape(Shape(L'☠', Color::GREY));
            mob->SetSpeed(120.0f);
            mob->SetAIRatio(0.5f);
            mob->SetMaxHp(100);
            mob->InitHp();
        }
        else if (i < section * 2)
        {
            render->SetShape(Shape(L'☣', Color::RED));
            mob->SetSpeed(70.0f);
            mob->SetAIRatio(1.0f);
            mob->SetMaxHp(100);
            mob->InitHp();
        }
        else if (i < section * 3)
        {
            render->SetShape(Shape(L'☯', Color::GREEN));
            mob->SetSpeed(30.0f);
            mob->SetAIRatio(1.5f);
            mob->SetMaxHp(100);
            mob->InitHp();
        }
        else if (i < section * 4)
        {
            render->SetShape(Shape(L'♋', Color::CYAN));
            mob->SetSpeed(30.0f);
            mob->SetAIRatio(1.5f);
            mob->SetMaxHp(100);
            mob->InitHp();
        }
        else
        {
            render->SetShape(Shape(L'★', Color::YELLOW));
            mob->SetSpeed(10.0f);
            mob->SetAIRatio(2.0f);
            mob->SetMaxHp(100);
            mob->InitHp();
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
        if (mob->IsDeath())
            continue;

        mob->AI(dt);
        mob->Update(dt);
    }
    m_Hero->Update(dt);
}

void Game::Render()
{
    for (auto& mob : m_MobList)
    {
        if (mob->IsDeath())
            continue;

        mob->Render();
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
    if (m_Command->IsKeyPress<Command::ENTER>())
    {
        GameManager::GetInstance().ReturnMain();
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
