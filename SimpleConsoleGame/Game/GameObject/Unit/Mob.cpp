#include "stdafx.h"
#include "Mob.h"
//----------------------------------------------------------------------------------------------------
#include "Core/Timer/Timer.h"
#include "Core/Console/Console.h"
#include "Core/ObjectPool/ObjectPool.h"
#include "Core/Game/Component/RenderComponent/CmdRenderComponent.h"
//----------------------------------------------------------------------------------------------------
#include "../Dummy.h"
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

    render->SetShape(Shape(L'●', Color::YELLOW));
    render->SetDepth(3);

    m_AITimer = ObjectPool<Timer>::Get(1.0f);
    m_HitMask = CollisionMask::ENEMY;
    m_AttackMask = CollisionMask::PLAYER;
}

void Mob::Release()
{
    m_AITimer.reset();
}

void Mob::Update(float dt)
{
    if (m_IsDeath)
        return;

    Vec2 displacement = m_ToPos - m_Pos;
    float distance = displacement.Length();
    if (distance < 1.0f)
    {
        m_MovePower.SetZero();
    }
    else
    {
        float maxMoveDist = m_Speed / m_MovePowerFrict;
        if (distance > maxMoveDist)
        {
            m_MovePower = displacement * (m_MovePowerLimit / distance);
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
    if (m_IsDeath)
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

        Vec2 displacement = m_ToPos - m_Pos;
        float distance = displacement.Length();
        if (distance < 1.0f)
        {
            m_MovePower.SetZero();
        }
        else
        {
            float maxMoveDist = m_Speed / m_MovePowerFrict;
            if (distance > maxMoveDist)
            {
                m_MovePower = displacement * (m_MovePowerLimit / distance);
            }
            else
            {
                m_MovePower = displacement * (m_MovePowerLimit / maxMoveDist);
            }
        }
    }
}
