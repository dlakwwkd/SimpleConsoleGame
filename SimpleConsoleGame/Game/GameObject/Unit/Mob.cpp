#include "stdafx.h"
#include "Mob.h"
//----------------------------------------------------------------------------------------------------
#include "Core/Timer/Timer.h"
#include "Core/Console/Console.h"
#include "Core/ObjectPool/ObjectPool.h"
#include "Core/Game/Component/RenderComponent/CmdRenderComponent.h"
#include "Core/Game/Composite/Effect/Dummy.h"
SCE_USE


Mob::Mob()
:   m_ToPos{ 0.0f, 0.0f },
    m_ToPosChangeProbability(0.2f)
{
    Init();
}


Mob::~Mob()
{
    Release();
}

void Mob::Init()
{
    auto render = GetComponent<CmdRenderComponent>();
    if (render == nullptr)
        return;

    render->SetShape(L'●', Color::YELLOW);
    render->SetDepth(3);

    m_AITimer = ObjectPool<Timer>::Get(1.0f);
    SetHitMask(CollisionMask::ENEMY);
    SetAttackMask(CollisionMask::PLAYER);
}

void Mob::Release()
{
    m_AITimer.reset();
}

void Mob::Update(float dt)
{
    if (IsDeath())
        return;

    Vec2 displacement = m_ToPos - GetPos();
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
    Unit::Update(dt);
}

void Mob::Render()
{
    Unit::Render();
}



void Mob::SetToPosChangeProbability(float prob)
{
    m_ToPosChangeProbability = prob;
}

void Mob::SetAIRatio(float ratio)
{
    if (m_AITimer)
    {
        m_AITimer->SetDuration(ratio);
    }
}

void Mob::AI(float dt)
{
    if (IsDeath())
        return;

    m_AITimer->AccumDt(dt);
    if (!m_AITimer->DurationCheck())
        return;

    int randRange = static_cast<int>(1.0f / m_ToPosChangeProbability);
    if (rand() % randRange == 0)
    {
        static auto& console = Console::GetInstance();
        auto toX = static_cast<float>(rand() % console.GetScreenWidth() / 2);
        auto toY = static_cast<float>(rand() % console.GetScreenHeight() - 1);
        m_ToPos.Set(toX, toY);

        Vec2 displacement = m_ToPos - GetPos();
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
