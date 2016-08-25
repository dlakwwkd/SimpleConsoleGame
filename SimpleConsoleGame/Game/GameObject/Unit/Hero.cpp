#include "stdafx.h"
#include "Hero.h"
//----------------------------------------------------------------------------------------------------
#include "Core/Timer/Timer.h"
#include "Core/Console/Console.h"
#include "Core/Game/Component/RenderComponent/CmdRenderComponent.h"
//----------------------------------------------------------------------------------------------------
#include "../Dummy.h"
SCE_USE


Hero::Hero()
{
    Init();
}


Hero::~Hero()
{
    Release();
}

void Hero::Init()
{
    auto render = GetComponent<CmdRenderComponent>();
    if (render == nullptr)
        return;

    render->SetShape(Shape(L'▣', Color::GREEN));
    render->SetDepth(5);
    m_MovePowerLimit = 0.2f;
    m_MovePowerFrict = 5.0f;
    m_Speed = 50.0f;
}

void Hero::Release()
{
}

void Hero::Update(float dt)
{
    Unit::Update(dt);
}

void Hero::Render()
{
    auto render = GetComponent<CmdRenderComponent>();
    if (render == nullptr)
        return;

    static Color color = render->GetColor();
    static Timer timer(1.0f);
    timer.Tick();
    timer.AccumDt();
    if (timer.DurationCheck())
    {
        render->SetColor(++color);
        /*
        std::thread([]()
        {
        Beep(524, 120);
        Beep(660, 120);
        Beep(784, 120);
        }
        ).detach();
        */
    }
    Unit::Render();
}
