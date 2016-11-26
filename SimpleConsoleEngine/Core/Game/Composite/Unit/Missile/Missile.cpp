#include "stdafx.h"
#include "Missile.h"
#include "../../Effect/Dummy.h"
#include "../../../GameManager.h"
#include "../../../Component/RenderComponent/CmdRenderComponent.h"
#include "../../../Component/CollisionComponent/CollisionComponent.h"
#include "../../../../Console/Console.h"
#include "../../../../Timer/Timer.h"
#include "../../../../Math/Vec2.h"
SCE_START


struct Missile::impl
{
    impl() noexcept
        : aiTimer{}
    {
    }

    std::shared_ptr<Timer> aiTimer;
};


Missile::Missile() noexcept
    : pimpl{ std::make_unique<impl>() }
{
}

Missile::~Missile()
{
}


void Missile::Init()
{
    Unit::Init();
    pimpl->aiTimer = ObjectPool<Timer>::Get(1.0f);
}

void Missile::Release()
{
    pimpl->aiTimer.reset();
    Unit::Release();
}

void Missile::Update(float _dt)
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
    Unit::Update(_dt);
}

void Missile::Death()
{
    auto collision = std::dynamic_pointer_cast<CollisionComponent>(GetCollision());
    if (!collision || collision->IsDeath())
        return;

    collision->Death();

    // 일단 하드코딩.. 나중에 제대로 구현하자
    static auto& gm = GameManager::GetInstance();
    gm.RemoveRender(std::dynamic_pointer_cast<IRenderObject>(shared_from_this()));
    auto effectCreate = [&](const Vec2& _createPos, float _craeteDelay)
    {
        auto effect = ObjectPool<Dummy>::GetWithInit();
        auto render = effect->GetComponent<CmdRenderComponent>();
        if (render != nullptr)
        {
            render->SetCoord(Coord(_createPos));
            render->SetShape(L'▒');
            render->SetColor(Color::YELLOW);
            render->SetBGColor(Color::RED);
            gm.CallFuncAfterM(_craeteDelay, &gm, &GameManager::AddRender, effect, 0.1f);
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



void Missile::SetAIRatio(float _ratio)
{
    if (pimpl->aiTimer)
    {
        pimpl->aiTimer->SetDuration(_ratio);
    }
}

void Missile::AI(float _dt)
{
}

SCE_END
