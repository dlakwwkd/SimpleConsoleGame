#include "stdafx.h"
#include "Game.h"
#include "Core/Math/Vec2.h"
#include "Core/Command/Command.h"
#include "Core/Console/Console.h"
#include "Core/Console/Coord.h"
#include "Core/Console/Color.hpp"
#include "Core/Console/Shape.h"
#include "Core/Game/GameManager.h"
#include "Core/Game/Component/RenderComponent/CmdRenderComponent.h"
#include "Core/Game/Component/CollisionComponent/CollisionComponent.h"
#include "Core/Game/Composite/Unit/LinkUnit/LinkedUnit.h"
#include "Core/Game/Composite/Camera/Camera.h"
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

    void        GenerateMob(size_t _num);
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
    static auto& gm = GameManager::GetInstance();
    gm.RegisterCollision(pimpl->hero);
    gm.AddRender(pimpl->hero);
    gm.GetMainCamera()->AttachToObject(pimpl->hero);
    gm.CallFuncAfterS(1.f,
        [=](int _d)
        {
           for (int i = 0; i < _d; ++i)
           {
               pimpl->GenerateMob(10);
           }
        }, 1);
}

void Game::Release()
{
    pimpl->mobList.clear();

    GameManager::GetInstance().RemoveRender(pimpl->hero);
    GameManager::GetInstance().UnRegisterCollision(pimpl->hero);
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


void Game::impl::GenerateMob(size_t _num)
{
    size_t mobType = _num / 5;
    for (size_t i = 0; i < _num; ++i)
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
            collision->SetMaxHp(300);
            collision->InitHp();
            mob->SetSpeed(120.0f);
            mob->SetAIRatio(0.5f);
            for (float i = 1; i < 7; ++i)
            {
                LinkedUnit::AddLinkedUnit(mob, Vec2::LEFT * i, render->GetShape());
                LinkedUnit::AddLinkedUnit(mob, Vec2::UP * i, render->GetShape());
                LinkedUnit::AddLinkedUnit(mob, Vec2::RIGHT * i, render->GetShape());
                LinkedUnit::AddLinkedUnit(mob, Vec2::DOWN * i, render->GetShape());
            }
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
            for (float i = 1; i < 6; ++i)
            {
                LinkedUnit::AddLinkedUnit(mob, Vec2::LEFT * i, render->GetShape(), true, 100);
                LinkedUnit::AddLinkedUnit(mob, Vec2::UP * i, render->GetShape(), true, 100);
                LinkedUnit::AddLinkedUnit(mob, Vec2::RIGHT * i, render->GetShape(), true, 100);
                LinkedUnit::AddLinkedUnit(mob, Vec2::DOWN * i, render->GetShape(), true, 100);
            }
            auto shape2 = render->GetShape();
            shape2.form = L'☢';
            shape2.color = Color::YELLOW;
            for (float i = 1; i < 5; ++i)
            {
                LinkedUnit::AddLinkedUnit(mob, Vec2::UP + Vec2::LEFT * i, shape2, false, 80);
                LinkedUnit::AddLinkedUnit(mob, Vec2::UP + Vec2::RIGHT * i, shape2, false, 80);
                LinkedUnit::AddLinkedUnit(mob, Vec2::DOWN + Vec2::LEFT * i, shape2, false, 80);
                LinkedUnit::AddLinkedUnit(mob, Vec2::DOWN + Vec2::RIGHT * i, shape2, false, 80);
            }
            auto shape3 = render->GetShape();
            shape3.form = L'❄';
            shape3.color = Color::GREEN;
            for (float i = 2; i < 5; ++i)
            {
                LinkedUnit::AddLinkedUnit(mob, Vec2::LEFT + Vec2::UP * i, shape3, false, 60);
                LinkedUnit::AddLinkedUnit(mob, Vec2::LEFT + Vec2::DOWN * i, shape3, false, 60);
                LinkedUnit::AddLinkedUnit(mob, Vec2::RIGHT + Vec2::UP * i, shape3, false, 60);
                LinkedUnit::AddLinkedUnit(mob, Vec2::RIGHT + Vec2::DOWN * i, shape3, false, 60);
            }
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
    if (command->IsKeyPress<Command::BUTTON_C>())
    {
        static auto& gm = GameManager::GetInstance();
        gm.GetMainCamera()->ChangeMoveTypeToNext();
    }
}
