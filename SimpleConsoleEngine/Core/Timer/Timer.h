#pragma once
SCE_START


class Timer
{
    SPECIALFUNC_SET(Timer, delete)
    using TickTime  = std::chrono::system_clock::time_point;
    using Seconds   = std::chrono::duration<float>;
public:
    Timer() noexcept;
    Timer(float duration) noexcept;

    void        Init() noexcept;
    void        Tick() noexcept;
    float       DeltaTime() const noexcept;

    void        AccumDt() noexcept;
    void        AccumDt(float dt) noexcept;
    bool        DurationCheck() noexcept;
    bool        DurationCheck(float duration) noexcept;
    void        SetDuration(float duration) noexcept;

private:
    TickTime    m_PrevTime;
    TickTime    m_CurrTime;
    Seconds     m_DeltaTime;

    float       m_AccumDt;
    float       m_Duration;
};

SCE_END
