#include "stdafx.h"
#include "Timer.h"


Timer::Timer() : m_SecondsPerCount(0.0), m_DeltaTime(0.0), m_PrevTime(0), m_CurrTime(0)
{
    LARGE_INTEGER li;
    QueryPerformanceFrequency(&li);
    m_SecondsPerCount = 1.0 / static_cast<double>(li.QuadPart);
}


Timer::~Timer()
{
}
