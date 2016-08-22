#include "stdafx.h"
#include "Missile.h"
//----------------------------------------------------------------------------------------------------
#include "SimpleConsoleEngine/Core/Console/Shape.hpp"
#include "SimpleConsoleEngine/Core/Timer/Timer.h"
//----------------------------------------------------------------------------------------------------
#include "../Dummy.h"
SCE_USE


Missile::Missile()
:   m_ToPos{ 0.0f, 0.0f },
    m_ToPosChangeProbability(0.2f)
{
    Init();
}


Missile::~Missile()
{
    Release();
}

void Missile::Init()
{
    m_ToPosShow = std::make_shared<Dummy>();
    m_AITimer = std::make_shared<Timer>(1.0f);
}

void Missile::Release()
{
    m_AITimer.reset();
    m_ToPosShow.reset();
}

void Missile::Update(float dt)
{
    Unit::Update(dt);
}

void Missile::Render()
{
    m_ToPosShow->Render();
    Unit::Render();
}



void Missile::AI(float dt)
{
}

void Missile::SetAIRatio(float ratio)
{
}
