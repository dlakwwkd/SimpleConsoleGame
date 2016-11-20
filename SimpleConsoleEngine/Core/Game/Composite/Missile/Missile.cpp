#include "stdafx.h"
#include "Missile.h"
#include "../Effect/Dummy.h"
#include "../../GameManager.h"
#include "../../Component/RenderComponent/CmdRenderComponent.h"
#include "../../Component/CollisionComponent/CollisionComponent.h"
#include "../../../ObjectPool/ObjectPool.h"
#include "../../../Console/Console.h"
#include "../../../Timer/Timer.h"
SCE_START


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
    const Vec2 bound(Coord::ConvertToVec2(console.GetScreenSize()));
    const Vec2 curPos = GetPos();
    if (curPos.GetX() < 0.1f
        || curPos.GetX() > bound.GetX() - 0.1f
        || curPos.GetY() < 0.1f
        || curPos.GetY() > bound.GetY() - 0.1f)
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
    if (IsDeath())
        return;

    auto collision = m_Collision.lock();
    if (collision == nullptr)
        return;

    collision->Death();

    // 일단 하드코딩.. 나중에 제대로 구현하자
    static auto& gm = GameManager::GetInstance();
    auto effectCreate = [&](const Vec2& createPos, float craeteDelay)
    {
        auto effect = ObjectPool<Dummy>::Get();
        auto render = effect->GetComponent<CmdRenderComponent>();
        if (render != nullptr)
        {
            render->SetCoord(Coord(createPos));
            render->SetShape(L'▒', Color::YELLOW, Color::RED);
            gm.CallFuncAfterM(craeteDelay, &gm, &GameManager::AddRender, effect, 0.1f);
        }
    };
    const int sequence = 10;
    const Vec2 curPos = GetPos();
    const Vec2 posArr[sequence] =
    {
        curPos,
        curPos + Vec2::UP,
        curPos + Vec2::UP + Vec2::RIGHT,
        curPos + Vec2::RIGHT,
        curPos + Vec2::RIGHT + Vec2::DOWN,
        curPos + Vec2::DOWN,
        curPos + Vec2::DOWN + Vec2::LEFT,
        curPos + Vec2::LEFT,
        curPos + Vec2::LEFT + Vec2::UP,
        curPos + Vec2::UP,
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

SCE_END
