#include "stdafx.h"
#include "Missile.h"
#include "../../Effect/Effect.h"
#include "../../../GameManager.h"
#include "../../../Component/RenderComponent.h"
#include "../../../Component/CollisionComponent.h"
#include "../../../../Console/Console.h"
#include "../../../../Console/Coord.h"
#include "../../../../Timer/Timer.h"
#include "../../../../Math/Vec2.h"
SCE_USE

/////////////////////////////////////////////////////////////////////////////////////////
struct Missile::impl
{
    impl() noexcept
        : aiTimer{}
    {
    }

    std::shared_ptr<Timer> aiTimer;
};

/////////////////////////////////////////////////////////////////////////////////////////
Missile::Missile() noexcept
    : pimpl{ std::make_unique<impl>() }
{
}

/////////////////////////////////////////////////////////////////////////////////////////
Missile::~Missile()
{
}

/////////////////////////////////////////////////////////////////////////////////////////
void Missile::Init()
{
    Unit::Init();
    pimpl->aiTimer = ObjectPool<Timer>::Get(1.0f);
}

/////////////////////////////////////////////////////////////////////////////////////////
void Missile::Release()
{
    pimpl->aiTimer.reset();
    Unit::Release();
}

/////////////////////////////////////////////////////////////////////////////////////////
void Missile::Update(float _dt)
{
    /*
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
    */
    Unit::Update(_dt);
}

/////////////////////////////////////////////////////////////////////////////////////////
void Missile::Death()
{
    Unit::Death();
}

/////////////////////////////////////////////////////////////////////////////////////////
void Missile::SetAIRatio(float _ratio)
{
    if (pimpl->aiTimer)
    {
        pimpl->aiTimer->SetDuration(_ratio);
    }
}

/////////////////////////////////////////////////////////////////////////////////////////
void Missile::AI(float _dt)
{
}
