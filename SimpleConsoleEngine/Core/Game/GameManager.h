﻿#pragma once
SCE_START
class IGameBase;
class Scheduler;
class Timer;


class GameManager
{
    CREATE_SINGLETON(GameManager)
public:
    template<IS_BASE_OF(GameType, IGameBase)>
    inline void Run();

    template<typename F, typename... Args>
    inline void CallFuncAfterS(float after, F&& functor, Args&&... args);

    template<typename T, typename F, typename... Args>
    inline void CallFuncAfterM(float after, T instance, F memfunc, Args&&... args);

    inline void ReturnMain() noexcept;
    inline void Shutdown() noexcept;

private:
    void    Init();
    void    Release();
    void    MainLoop();
    void    GameLoop();

    void    UpdateProcess();
    void    RenderProcess();

    float   FrameProgress() noexcept;
    void    SetRenderLimit(size_t limitFrame) noexcept;
    bool    RenderLimitCheck() noexcept;
    void    PrintFrame();

private:
    std::unique_ptr<IGameBase>  m_Game;
    std::unique_ptr<Scheduler>  m_Scheduler;
    std::unique_ptr<Timer>      m_Timer;
    bool                        m_IsRun;
    bool                        m_IsPlay;
    size_t                      m_FrameCount;
    size_t                      m_RenderCount;
    size_t                      m_RenderLimit;
};

SCE_END
#include "GameManager.inl"
