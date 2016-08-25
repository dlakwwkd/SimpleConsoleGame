#pragma once
SCE_START


class Timer
{
    SPECIALFUNC_SET(Timer, delete)
    using TickTime  = std::chrono::system_clock::time_point;
    using Seconds   = std::chrono::duration<float>;
public:
    Timer();
    Timer(float duration);

    void    Init();
    void    Tick();
    float   DeltaTime() const;

    void    AccumDt();
    void    AccumDt(float dt);
    bool    DurationCheck();
    bool    DurationCheck(float duration);
    void    SetDuration(float duration);

private:
    TickTime    m_PrevTime;
    TickTime    m_CurrTime;
    Seconds     m_DeltaTime;

    float       m_AccumDt;
    float       m_Duration;
};

SCE_END
