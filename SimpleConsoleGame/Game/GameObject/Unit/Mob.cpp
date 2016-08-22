#include "stdafx.h"
#include "Mob.h"
//----------------------------------------------------------------------------------------------------
#include "SimpleConsoleEngine/Core/Timer/Timer.h"
#include "SimpleConsoleEngine/Core/Game/Component/CmdRenderComponent.h"
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

    m_ToPosShow = std::make_shared<Dummy>();
    auto dummyRender = m_ToPosShow->GetComponent<CmdRenderComponent>();
    if (dummyRender == nullptr)
        return;

    dummyRender->SetShape(Shape(L'✘', Color::MAGENTA));
    dummyRender->SetShow(false);
    dummyRender->SetDepth(1);

    m_AITimer = std::make_shared<Timer>(1.0f);
}

void Mob::Release()
{
    m_AITimer.reset();
    m_ToPosShow.reset();
}

void Mob::Update(float dt)
{
    Vec2 displacement = m_ToPos - m_Pos;
    float distance = displacement.Length();
    if (distance < 1.0f)
    {
        m_MovePower.SetZero();
        auto render = m_ToPosShow->GetComponent<CmdRenderComponent>();
        if (render != nullptr)
        {
            render->SetShow(false);
        }
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
    m_ToPosShow->Render();
    Unit::Render();
}



void Mob::AI(float dt)
{
    m_AITimer->AccumDt(dt);
    if (!m_AITimer->DurationCheck())
    {
        return;
    }
    int randRange = static_cast<int>(1.0f / m_ToPosChangeProbability);
    if (rand() % randRange == 0)
    {
        static auto& console = Console::GetInstance();
        auto toX = static_cast<float>(rand() % console.GetScreenWidth() / 2);
        auto toY = static_cast<float>(rand() % console.GetScreenHeight() - 1);
        m_ToPos.Set(toX, toY);

        auto render = m_ToPosShow->GetComponent<CmdRenderComponent>();
        if (render != nullptr)
        {
            render->SetCoord(static_cast<short>(m_ToPos.GetX() * 2.0f), static_cast<short>(m_ToPos.GetY()));
            render->SetShow(true);
        }

        Vec2 displacement = m_ToPos - m_Pos;
        float distance = displacement.Length();
        if (distance < 1.0f)
        {
            m_MovePower.SetZero();
            render->SetShow(false);
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

void Mob::SetAIRatio(float ratio)
{
    if (m_AITimer)
    {
        m_AITimer->SetDuration(ratio);
    }
}
