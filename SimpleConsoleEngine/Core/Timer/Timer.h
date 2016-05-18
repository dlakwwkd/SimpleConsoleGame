#pragma once
SCE_START


class Timer
{
    SPECIALFUNC_SET(Timer, delete)
public:
    SCE_API inline Timer() noexcept;
    SCE_API inline Timer(float duration) noexcept;

    SCE_API inline void     Init() noexcept;
    SCE_API inline void     Tick() noexcept;
    SCE_API inline float    DeltaTime() const noexcept;

    SCE_API inline void     AccumDt() noexcept;
    SCE_API inline void     AccumDt(float dt) noexcept;
    SCE_API inline bool     DurationCheck() noexcept;
    SCE_API inline bool     DurationCheck(float duration) noexcept;
    SCE_API inline void     SetDuration(float duration) noexcept;

private:
    using TickTime  = std::chrono::system_clock::time_point;
    using Seconds   = std::chrono::duration<float>;

    TickTime    m_PrevTime;
    TickTime    m_CurrTime;
    Seconds     m_DeltaTime;

    float       m_AccumDt;
    float       m_Duration;
};

SCE_END
#include "Timer.inl"
