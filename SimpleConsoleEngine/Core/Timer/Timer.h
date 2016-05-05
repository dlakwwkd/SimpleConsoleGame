#pragma once
SCE_START


class SCE_API Timer
{
public:
    Timer() noexcept;

    inline void     Init() noexcept;
    inline void     Tick() noexcept;
    inline float    DeltaTime() const noexcept;

private:
    double          m_SecondsPerCount;
    double          m_DeltaTime;
    __int64         m_PrevTime;
    __int64         m_CurrTime;
};

SCE_END
#include "Timer.inl"
