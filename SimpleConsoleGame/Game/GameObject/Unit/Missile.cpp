#include "stdafx.h"
#include "Missile.h"
//----------------------------------------------------------------------------------------------------
#include "Core/Console/Shape.h"
#include "Core/Console/Console.h"
#include "Core/Timer/Timer.h"
#include "Core/Game/Component/RenderComponent/CmdRenderComponent.h"
#include "Core/Game/GameManager.h"
#include "Core/ObjectPool/ObjectPool.h"
//----------------------------------------------------------------------------------------------------
#include "../Dummy.h"
#include "../../Game.h"
SCE_USE


Missile::Missile()
{
    Init();
}


Missile::~Missile()
{
    Release();
}

void Missile::Init()
{
    m_AITimer = ObjectPool<Timer>::Get(1.0f);
}

void Missile::Release()
{
    m_AITimer.reset();
}

void Missile::Update(float dt)
{
    static auto& console = Console::GetInstance();
    Vec2 bound(Coord::ConvertToVec2(console.GetScreenSize()));
    if (m_Pos.GetX() < 0.1f
        || m_Pos.GetX() > bound.GetX() - 0.1f
        || m_Pos.GetY() < 0.1f
        || m_Pos.GetY() > bound.GetY() - 0.1f)
    {
        Death();
    }
    Unit::Update(dt);
}

void Missile::Render()
{
    Unit::Render();
}

void Missile::Death()
{
    if (m_IsDeath)
        return;

    m_IsDeath = true;

    // 일단 하드코딩.. 나중에 제대로 구현하자
    static auto& gm = GameManager::GetInstance();
    auto& game = gm.GetGame<Game>();
    auto effectCreate = [&](const Vec2& createPos, float craeteDelay)
    {
        auto effect = ObjectPool<Dummy>::Get();
        auto render = effect->GetComponent<CmdRenderComponent>();
        if (render != nullptr)
        {
            render->SetCoord(Coord(createPos));
            render->SetShape(Shape(L'▒', Color::YELLOW, Color::RED));
            gm.CallFuncAfterM(craeteDelay, &game, &Game::AddOnlyRender, effect, 0.1f);
        }
    };
    const int sequence = 10;
    const Vec2 posArr[sequence] =
    {
        m_Pos,
        m_Pos + Vec2::UP,
        m_Pos + Vec2::UP + Vec2::RIGHT,
        m_Pos + Vec2::RIGHT,
        m_Pos + Vec2::RIGHT + Vec2::DOWN,
        m_Pos + Vec2::DOWN,
        m_Pos + Vec2::DOWN + Vec2::LEFT,
        m_Pos + Vec2::LEFT,
        m_Pos + Vec2::LEFT + Vec2::UP,
        m_Pos + Vec2::UP,
    };
    for (int i = 0; i < sequence; ++i)
    {
        effectCreate(posArr[i], 0.02f * i);
    }
}



void Missile::SetAIRatio(float ratio)
{
    if (m_AITimer)
    {
        m_AITimer->SetDuration(ratio);
    }
}

void Missile::AI(float dt)
{
}
