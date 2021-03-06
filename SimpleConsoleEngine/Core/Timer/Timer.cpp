﻿#include "stdafx.h"
#include "Timer.h"
SCE_USE

/////////////////////////////////////////////////////////////////////////////////////////
Timer::Timer() noexcept
    : prevTime{ std::chrono::system_clock::now() }
    , curTime{}
    , deltaTime{}
    , accumDt{}
    , duration{}
{
}

/////////////////////////////////////////////////////////////////////////////////////////
Timer::Timer(float _duration) noexcept
    : prevTime{ std::chrono::system_clock::now() }
    , curTime{}
    , deltaTime{}
    , accumDt{ _duration + 1.f }
    , duration{ _duration }
{
}

/////////////////////////////////////////////////////////////////////////////////////////
void Timer::Init() noexcept
{
    prevTime = std::chrono::system_clock::now();
    accumDt = 0.0f;
}

/////////////////////////////////////////////////////////////////////////////////////////
void Timer::Tick() noexcept
{
    curTime = std::chrono::system_clock::now();
    deltaTime = curTime - prevTime;
    prevTime = curTime;
}

/////////////////////////////////////////////////////////////////////////////////////////
float Timer::DeltaTime() const noexcept
{
    return deltaTime.count();
}

/////////////////////////////////////////////////////////////////////////////////////////
// Tick을 직접 하는 경우
void Timer::AccumDt() noexcept
{
    accumDt += deltaTime.count();
}

/////////////////////////////////////////////////////////////////////////////////////////
// Tick을 직접 하지 않는 경우
void Timer::AccumDt(float _dt) noexcept
{
    accumDt += _dt;
}

/////////////////////////////////////////////////////////////////////////////////////////
// 타이머 생성시 Duration을 지정한 경우
bool Timer::DurationCheck() noexcept
{
    if (accumDt > duration)
    {
        accumDt = 0.0f;
        return true;
    }
    return false;
}

/////////////////////////////////////////////////////////////////////////////////////////
// 고정 Duration이 아닌 경우
bool Timer::DurationCheck(float _duration) noexcept
{
    if (accumDt > _duration)
    {
        accumDt = 0.0f;
        return true;
    }
    return false;
}

/////////////////////////////////////////////////////////////////////////////////////////
void Timer::SetDuration(float _duration) noexcept
{
    duration = _duration;
}
