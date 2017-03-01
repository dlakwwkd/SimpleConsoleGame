#include "stdafx.h"
#include "Mob.h"
#include "Core/Math/Vec2.h"
#include "Core/Timer/Timer.h"
#include "Core/Console/Console.h"
#include "Core/Console/Coord.h"
#include "Core/Console/Color.hpp"
#include "Core/Game/Component/RenderComponent/CmdRenderComponent.h"
#include "Core/Game/Component/CollisionComponent/CollisionComponent.h"
SCE_USE


struct Mob::impl
{
    impl() noexcept
        : aiTimer{}
        , toPos{}
        , toPosChangeProbability{ 0.2f }
    {
    }

    std::shared_ptr<Timer>  aiTimer;
    Vec2                    toPos;
    float                   toPosChangeProbability;
};


Mob::Mob() noexcept
    : pimpl{ std::make_unique<impl>() }
{
}

Mob::~Mob()
{
}


void Mob::Init()
{
    Unit::Init();
    auto render = IRenderObject::Get<CmdRenderComponent>();
    if (render == nullptr)
        return;

    render->SetShape(L'●');
    render->SetColor(Color::YELLOW);
    render->SetDepth(3);

    auto collision = ICollisionObject::Get<CollisionComponent>();
    if (collision == nullptr)
        return;

    pimpl->aiTimer = ObjectPool<Timer>::Get(1.0f);
    collision->SetHitMask(CollisionComponent::CollisionMask::ENEMY);
    collision->SetAttackMask(CollisionComponent::CollisionMask::PLAYER);
}

void Mob::Release()
{
    pimpl->aiTimer.reset();
    Unit::Release();
}

void Mob::Update(float _dt)
{
    auto collision = ICollisionObject::Get<CollisionComponent>();
    if (!collision || collision->IsDeath())
        return;

    Vec2 displacement = pimpl->toPos - GetPos();
    float distance = displacement.Length();
    if (distance < 1.0f)
    {
        SetMovePower(Vec2::ZERO);
    }
    else
    {
        float maxMoveDist = GetSpeed() / GetMovePowerFrict();
        if (distance > maxMoveDist)
        {
            SetMovePower(displacement * (GetMovePowerLimit() / distance));
        }
    }
    Unit::Update(_dt);
}

void Mob::Render()
{
    Unit::Render();
}



void Mob::SetToPosChangeProbability(float _prob)
{
    pimpl->toPosChangeProbability = _prob;
}

void Mob::SetAIRatio(float _ratio)
{
    if (pimpl->aiTimer)
    {
        pimpl->aiTimer->SetDuration(_ratio);
    }
}

void Mob::AI(float _dt)
{
    auto collision = ICollisionObject::Get<CollisionComponent>();
    if (!collision || collision->IsDeath())
        return;

    pimpl->aiTimer->AccumDt(_dt);
    if (!pimpl->aiTimer->DurationCheck())
        return;

    int randRange = static_cast<int>(1.0f / pimpl->toPosChangeProbability);
    if (rand() % randRange == 0)
    {
        static auto& console = Console::GetInstance();
        auto toX = static_cast<float>(rand() % console.GetScreenWidth() / 2);
        auto toY = static_cast<float>(rand() % console.GetScreenHeight() - 1);
        pimpl->toPos.Set(toX, toY);

        Vec2 displacement = pimpl->toPos - GetPos();
        float distance = displacement.Length();
        if (distance < 1.0f)
        {
            SetMovePower(Vec2::ZERO);
        }
        else
        {
            float maxMoveDist = GetSpeed() / GetMovePowerFrict();
            if (distance > maxMoveDist)
            {
                SetMovePower(displacement * (GetMovePowerLimit() / distance));
            }
            else
            {
                SetMovePower(displacement * (GetMovePowerLimit() / maxMoveDist));
            }
        }
    }
}
