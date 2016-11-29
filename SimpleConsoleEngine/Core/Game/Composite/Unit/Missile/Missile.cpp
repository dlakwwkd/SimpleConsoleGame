#include "stdafx.h"
#include "Missile.h"
#include "../../Effect/Effect.h"
#include "../../../GameManager.h"
#include "../../../EffectManager.h"
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
        , explosionEffect{ EffectType::EXPLOSION_A }
    {
    }

    std::shared_ptr<Timer>  aiTimer;
    EffectType              explosionEffect;
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
    auto collision = ICollisionObject::Get<CollisionComponent>();
    if (!collision || collision->IsDeath())
        return;

    collision->Death();

    static auto& gm = GameManager::GetInstance();
    static auto& em = EffectManager::GetInstance();
    gm.RemoveRender(std::dynamic_pointer_cast<IRenderObject>(shared_from_this()));
    em.PlayEffect(GetPos(), pimpl->explosionEffect);
}


void Missile::SetExplosionEffect(EffectType _type) noexcept
{
    pimpl->explosionEffect = _type;
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
