#include "stdafx.h"
#include "Timer.h"
SCE_START


Timer::Timer()
:   m_PrevTime(std::chrono::system_clock::now()),
    m_CurrTime(),
    m_DeltaTime(0.0f),
    m_AccumDt(0.0f),
    m_Duration(0.0f)
{
}

Timer::Timer(float duration)
:   m_PrevTime(std::chrono::system_clock::now()),
    m_CurrTime(),
    m_DeltaTime(0.0f),
    m_AccumDt(0.0f),
    m_Duration(duration)
{
}


void Timer::Init()
{
    m_PrevTime = std::chrono::system_clock::now();
    m_AccumDt = 0.0f;
}

void Timer::Tick()
{
    m_CurrTime = std::chrono::system_clock::now();
    m_DeltaTime = m_CurrTime - m_PrevTime;
    m_PrevTime = m_CurrTime;
}

float Timer::DeltaTime() const
{
    return m_DeltaTime.count();
}



// Tick을 직접 하는 경우
void Timer::AccumDt()
{
    m_AccumDt += m_DeltaTime.count();
}

// Tick을 직접 하지 않는 경우
void Timer::AccumDt(float dt)
{
    m_AccumDt += dt;
}

// 타이머 생성시 Duration을 지정한 경우
bool Timer::DurationCheck()
{
    if (m_AccumDt > m_Duration)
    {
        m_AccumDt = 0.0f;
        return true;
    }
    return false;
}

// 고정 Duration이 아닌 경우
bool Timer::DurationCheck(float duration)
{
    if (m_AccumDt > duration)
    {
        m_AccumDt = 0.0f;
        return true;
    }
    return false;
}

void Timer::SetDuration(float duration)
{
    m_Duration = duration;
}

SCE_END
