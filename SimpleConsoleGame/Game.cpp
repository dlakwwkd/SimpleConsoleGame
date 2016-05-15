#include "stdafx.h"
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
    SetRenderFrameLimit(60);

    m_Command = std::make_unique<Command>();
    m_Hero = std::make_unique<Hero>();
    m_MobList.resize(30);
    for (size_t i = 0; i < 30; ++i)
    {
        if (i < 5)
        {
            m_MobList[i].SetShape(Shape(L'●', Color::BLUE));
            m_MobList[i].SetSpeed(120.0f);
        }
        else if (i < 12)
        {
            m_MobList[i].SetShape(Shape(L'火', Color::RED));
            m_MobList[i].SetSpeed(70.0f);
        }
        else if (i < 20)
        {
            m_MobList[i].SetShape(Shape(L'⊙', Color::GREEN));
            m_MobList[i].SetSpeed(30.0f);
        }
        else
        {
            m_MobList[i].SetShape(Shape(L'★', Color::YELLOW));
            m_MobList[i].SetSpeed(10.0f);
        }
    }
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
    static auto& console = Console::GetInstance();
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
        m_Hero->AddMovePower(Vec2::UP * dt);
    }
    if (m_Command->IsKeyPress(Command::DOWN))
    {
        m_Hero->AddMovePower(Vec2::DOWN * dt);
    }
    if (m_Command->IsKeyPress(Command::LEFT))
    {
        m_Hero->AddMovePower(Vec2::LEFT * dt);
    }
    if (m_Command->IsKeyPress(Command::RIGHT))
    {
        m_Hero->AddMovePower(Vec2::RIGHT * dt);
    }
    if (m_Command->IsKeyPress(Command::BUTTON_A))
    {
    }
}

void Game::FrameShow()
{
    static auto& console = Console::GetInstance();

    std::wostringstream oss;
    oss << L"UpdateFrame: " << m_FrameRate << L"\t"
        << L"RenderFrame: " << m_RenderCount << L"/" << m_RenderRate << L"\t"
        << L"DrawCall: " << console.GetDrawCallNum();

    console.SetColor(Color::WHITE);
    console.PrintText(Coord(0, console.GetScreenHeight() + 1), oss.str().c_str());
}
