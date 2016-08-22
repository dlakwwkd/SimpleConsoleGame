#pragma once
SCE_START


class Timer
{
    SPECIALFUNC_SET(Timer, delete)
public:
    inline Timer() noexcept;
    inline Timer(float duration) noexcept;

    inline void     Init() noexcept;
    inline void     Tick() noexcept;
    inline float    DeltaTime() const noexcept;

    inline void     AccumDt() noexcept;
    inline void     AccumDt(float dt) noexcept;
    inline bool     DurationCheck() noexcept;
    inline bool     DurationCheck(float duration) noexcept;
    inline void     SetDuration(float duration) noexcept;

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
