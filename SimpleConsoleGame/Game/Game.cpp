#include "stdafx.h"
#include "Game.h"
#include "Core/Math/Vec2.h"
#include "Core/Command/Command.h"
#include "Core/Console/Console.h"
#include "Core/Console/Coord.h"
#include "Core/Console/Color.hpp"
#include "Core/Game/GameManager.h"
#include "Core/Game/Component/RenderComponent/CmdRenderComponent.h"
#include "Core/Game/Component/CollisionComponent/CollisionComponent.h"
#include "GameObject/Unit/Hero.h"
#include "GameObject/Unit/Mob.h"
SCE_USE


struct Game::impl
{
    impl() noexcept
        : command{}
        , hero{}
        , mobList{}
    {
    }

    void        GenerateMob(int _num);
    void        CommandProc(float _dt) const;

    CommandPtr  command;
    HeroPtr     hero;
    MobList     mobList;
};


Game::Game() noexcept
    : pimpl{ std::make_unique<impl>() }
{
}

Game::~Game()
{
}


void Game::Init()
{
    srand((unsigned int)time(NULL));

    pimpl->command = std::make_unique<Command>();
    pimpl->hero = ObjectPool<Hero>::GetWithInit();
    pimpl->hero->SetDefaultAttack();
    GameManager::GetInstance().RegisterCollision(pimpl->hero);
    GameManager::GetInstance().AddRender(pimpl->hero);

    pimpl->GenerateMob(50);
}

void Game::Release()
{
    pimpl->mobList.clear();
    pimpl->hero.reset();
    pimpl->command.reset();
}

void Game::Update(float _dt)
{
    pimpl->CommandProc(_dt);
    for (auto iter = pimpl->mobList.begin(); iter != pimpl->mobList.end();)
    {
        auto& mob = *iter;
        auto& collision = mob->GetCollision();
        if (!collision || collision->IsDeath())
        {
            iter = pimpl->mobList.erase(iter);
            continue;
        }
        mob->AI(_dt);
        ++iter;
    }
}

void Game::Render()
{
    static auto& console = Console::GetInstance();
    std::wostringstream oss;
    oss << L"MobNum: " << pimpl->mobList.size();
    size_t posX = (console.GetScreenWidth() - oss.str().length()) / 2;
    size_t posY = console.GetScreenHeight() + 1;
    console.PrintText(Coord(posX, posY), oss.str());
}


void Game::impl::GenerateMob(int _num)
{
    int mobType = _num / 5;
    for (int i = 0; i < _num; ++i)
    {
        auto mob = ObjectPool<Mob>::GetWithInit();
        mobList.push_back(mob);

        auto& render = mob->GetRender();
        if (render == nullptr)
            continue;

        auto& collision = mob->GetCollision();
        if (collision == nullptr)
            continue;

        GameManager::GetInstance().RegisterCollision(mob);
        GameManager::GetInstance().AddRender(mob);
        if (i < mobType)
        {
            render->SetShape(L'☠');
            render->SetColor(Color::GREY);
            collision->SetDamage(2);
            collision->SetMaxHp(100);
            collision->InitHp();
            mob->SetSpeed(120.0f);
            mob->SetAIRatio(0.5f);
        }
        else if (i < mobType * 2)
        {
            render->SetShape(L'☣');
            render->SetColor(Color::RED);
            collision->SetDamage(4);
            collision->SetMaxHp(100);
            collision->InitHp();
            mob->SetSpeed(70.0f);
            mob->SetAIRatio(1.0f);
        }
        else if (i < mobType * 3)
        {
            render->SetShape(L'☯');
            render->SetColor(Color::MAGENTA);
            collision->SetDamage(6);
            collision->SetMaxHp(100);
            collision->InitHp();
            mob->SetSpeed(30.0f);
            mob->SetAIRatio(1.5f);
        }
        else if (i < mobType * 4)
        {
            render->SetShape(L'♋');
            render->SetColor(Color::CYAN);
            collision->SetDamage(8);
            collision->SetMaxHp(100);
            collision->InitHp();
            mob->SetSpeed(30.0f);
            mob->SetAIRatio(1.5f);
        }
        else
        {
            render->SetShape(L'★');
            render->SetColor(Color::YELLOW);
            collision->SetDamage(10);
            collision->SetMaxHp(100);
            collision->InitHp();
            mob->SetSpeed(10.0f);
            mob->SetAIRatio(2.0f);
        }
    }
}

void Game::impl::CommandProc(float _dt) const
{
    if (command->IsKeyPress<Command::ESC>())
    {
        GameManager::GetInstance().Shutdown();
        return;
    }
    if (command->IsKeyPress<Command::ENTER>())
    {
        GameManager::GetInstance().ReturnMain();
        return;
    }
    if (command->IsKeyPress<Command::UP>())
    {
        hero->AddMovePower(Vec2::UP * _dt);
    }
    if (command->IsKeyPress<Command::DOWN>())
    {
        hero->AddMovePower(Vec2::DOWN * _dt);
    }
    if (command->IsKeyPress<Command::LEFT>())
    {
        hero->AddMovePower(Vec2::LEFT * _dt);
    }
    if (command->IsKeyPress<Command::RIGHT>())
    {
        hero->AddMovePower(Vec2::RIGHT * _dt);
    }
    if (command->IsKeyPress<Command::BUTTON_A>())
    {
        hero->ShootMissile();
    }
    if (command->IsKeyPress<Command::BUTTON_B>())
    {
        hero->SwapMissile();
    }
}
