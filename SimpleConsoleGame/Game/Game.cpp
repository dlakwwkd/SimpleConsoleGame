#include "stdafx.h"
#include "Game.h"
//----------------------------------------------------------------------------------------------------
#include "Core/Timer/Timer.h"
#include "Core/Command/Command.h"
#include "Core/Console/Console.h"
#include "Core/ObjectPool/ObjectPool.h"
#include "Core/Game/Section.h"
#include "Core/Game/GameManager.h"
#include "Core/Game/Component/RenderComponent/CmdRenderComponent.h"
#include "Core/Game/Composite/Effect/Dummy.h"
#include "Core/Game/Composite/Unit/Unit.h"
#include "Core/Game/Composite/Missile/Missile.h"
//----------------------------------------------------------------------------------------------------
#include "GameObject/Unit/Hero.h"
#include "GameObject/Unit/Mob.h"
SCE_USE


Game::Game() noexcept
{
}


Game::~Game()
{
}

void Game::Init()
{
    srand((unsigned int)time(NULL));

    m_Command = std::make_unique<Command>();
    m_Hero = ObjectPool<Hero>::GetWithInit();
    m_Hero->SetDefaultAttack();
    GameManager::GetInstance().RegisterCollision(m_Hero);
    GameManager::GetInstance().AddRender(m_Hero);

    GenerateMob(100);
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
        mob->AI(dt);
    }
}

void Game::Render()
{
}


void Game::GenerateMob(int num)
{
    int mobType = num / 5;
    m_MobList.reserve(num);
    for (int i = 0; i < num; ++i)
    {
        m_MobList.emplace_back(ObjectPool<Mob>::GetWithInit());
        auto& mob = m_MobList[i];
        auto render = mob->GetComponent<CmdRenderComponent>();
        if (render == nullptr)
            continue;

        GameManager::GetInstance().RegisterCollision(mob);
        GameManager::GetInstance().AddRender(mob);
        if (i < mobType)
        {
            render->SetShape(L'☠', Color::GREY);
            mob->SetSpeed(120.0f);
            mob->SetAIRatio(0.5f);
            mob->SetDamage(2);
            mob->SetMaxHp(100);
            mob->InitHp();
        }
        else if (i < mobType * 2)
        {
            render->SetShape(L'☣', Color::RED);
            mob->SetSpeed(70.0f);
            mob->SetAIRatio(1.0f);
            mob->SetDamage(4);
            mob->SetMaxHp(100);
            mob->InitHp();
        }
        else if (i < mobType * 3)
        {
            render->SetShape(L'☯', Color::MAGENTA);
            mob->SetSpeed(30.0f);
            mob->SetAIRatio(1.5f);
            mob->SetDamage(6);
            mob->SetMaxHp(100);
            mob->InitHp();
        }
        else if (i < mobType * 4)
        {
            render->SetShape(L'♋', Color::CYAN);
            mob->SetSpeed(30.0f);
            mob->SetAIRatio(1.5f);
            mob->SetDamage(8);
            mob->SetMaxHp(100);
            mob->InitHp();
        }
        else
        {
            render->SetShape(L'★', Color::YELLOW);
            mob->SetSpeed(10.0f);
            mob->SetAIRatio(2.0f);
            mob->SetDamage(10);
            mob->SetMaxHp(100);
            mob->InitHp();
        }
    }
}

void Game::CommandProc(float dt) const
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
        m_Hero->ShootMissile();
    }
    if (m_Command->IsKeyPress<Command::BUTTON_B>())
    {
        m_Hero->SwapMissile();
    }
}
