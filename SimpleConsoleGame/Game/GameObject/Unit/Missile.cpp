#include "stdafx.h"
#include "Missile.h"
//----------------------------------------------------------------------------------------------------
#include "Core/Console/Shape.h"
#include "Core/Console/Console.h"
#include "Core/Timer/Timer.h"
//----------------------------------------------------------------------------------------------------
#include "../Dummy.h"
SCE_USE


Missile::Missile()
:   m_ToPos{ 0.0f, 0.0f },
    m_ToPosChangeProbability(0.0f)
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



void Missile::SetToPosChangeProbability(float prob)
{
    m_ToPosChangeProbability = prob;
}

void Missile::SetAIRatio(float ratio)
{
}



void Missile::AI(float dt)
{
}
