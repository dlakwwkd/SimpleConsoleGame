#include "stdafx.h"
#include "Timer.h"
SCE_START


Timer::Timer() noexcept
    : m_PrevTime(std::chrono::system_clock::now())
    , m_CurrTime()
    , m_DeltaTime(0.0f)
    , m_AccumDt(0.0f)
    , m_Duration(0.0f)
{
}

Timer::Timer(float duration) noexcept
    : m_PrevTime(std::chrono::system_clock::now())
    , m_CurrTime()
    , m_DeltaTime(0.0f)
    , m_AccumDt(0.0f)
    , m_Duration(duration)
{
}


void Timer::Init() noexcept
{
    m_PrevTime = std::chrono::system_clock::now();
    m_AccumDt = 0.0f;
}

void Timer::Tick() noexcept
{
    m_CurrTime = std::chrono::system_clock::now();
    m_DeltaTime = m_CurrTime - m_PrevTime;
    m_PrevTime = m_CurrTime;
}

float Timer::DeltaTime() const noexcept
{
    return m_DeltaTime.count();
}


// Tick을 직접 하는 경우
void Timer::AccumDt() noexcept
{
    m_AccumDt += m_DeltaTime.count();
}

// Tick을 직접 하지 않는 경우
void Timer::AccumDt(float dt) noexcept
{
    m_AccumDt += dt;
}

// 타이머 생성시 Duration을 지정한 경우
bool Timer::DurationCheck() noexcept
{
    if (m_AccumDt > m_Duration)
    {
        m_AccumDt = 0.0f;
        return true;
    }
    return false;
}

// 고정 Duration이 아닌 경우
bool Timer::DurationCheck(float duration) noexcept
{
    if (m_AccumDt > duration)
    {
        m_AccumDt = 0.0f;
        return true;
    }
    return false;
}

void Timer::SetDuration(float duration) noexcept
{
    m_Duration = duration;
}

SCE_END
