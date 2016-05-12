#include "stdafx.h"
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
    SetRenderLimitFrame(60);

    m_Command = std::make_unique<Command>();
    m_Unit = std::make_unique<Unit>();
    m_MobList.resize(100);
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
    FrameCalc(dt);
    CommandProc(dt);

    for (auto& mob : m_MobList)
    {
        mob.AI(dt);
        mob.Update(dt);
    }
    m_Unit->Update(dt);

    static Color color = Color::GREY;
    static float limit = 0.1f;
    static float stack = 0.0f;
    stack += dt;
    if (stack > limit)
    {
        m_Unit->SetShape(Shape(L'▣', ++color, Color::BLACK));
        stack = 0.0f;
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

    std::wostringstream oss;
    oss << L"UpdateFrame: " << m_FrameRate << L"\n"
        << L"RenderFrame: " << m_RenderCount << L"/" << m_RenderRate;
    console.SetColor(Color::WHITE);
    console.Print(Coord(0, 0), oss.str().c_str());

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
