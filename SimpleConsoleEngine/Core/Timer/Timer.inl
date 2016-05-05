SCE_START


inline void Timer::Init() noexcept
{
    LARGE_INTEGER li;
    QueryPerformanceCounter(&li);
    m_PrevTime = li.QuadPart;
}

inline void Timer::Tick() noexcept
{
    LARGE_INTEGER li;
    QueryPerformanceCounter(&li);
    m_CurrTime = li.QuadPart;

    m_DeltaTime = (m_CurrTime - m_PrevTime)*m_SecondsPerCount;
    m_PrevTime = m_CurrTime;
}

inline float Timer::DeltaTime() const noexcept
{
    return static_cast<float>(m_DeltaTime);
}

SCE_END
