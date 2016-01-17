#pragma once
class Timer
{
public:
    Timer();

    inline void     Init();
    inline void     Tick();
    inline float    DeltaTime() const;
private:
    double          m_SecondsPerCount;
    double          m_DeltaTime;
    __int64         m_PrevTime;
    __int64         m_CurrTime;
};
#include "Timer.inl"
