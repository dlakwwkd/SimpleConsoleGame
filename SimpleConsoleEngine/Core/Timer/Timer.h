#pragma once
SCE_START

/////////////////////////////////////////////////////////////////////////////////////////
class Timer
{
    SPECIALFUNC_SET(Timer, delete)
    using TickTime  = std::chrono::system_clock::time_point;
    using Seconds   = std::chrono::duration<float>;
public:
    Timer() noexcept;
    Timer(float _duration) noexcept;

    void        Init() noexcept;
    void        Tick() noexcept;
    float       DeltaTime() const noexcept;

    void        AccumDt() noexcept;
    void        AccumDt(float _dt) noexcept;
    bool        DurationCheck() noexcept;
    bool        DurationCheck(float _duration) noexcept;
    void        SetDuration(float _duration) noexcept;

private:
    TickTime    prevTime;
    TickTime    curTime;
    Seconds     deltaTime;
    float       accumDt;
    float       duration;
};

SCE_END
