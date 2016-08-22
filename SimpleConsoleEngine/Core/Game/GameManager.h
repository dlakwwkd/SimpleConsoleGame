#pragma once
#include "Scheduler.hpp"
SCE_START
class GameBase;
class Timer;


class GameManager
{
    CREATE_SINGLETON(GameManager)
public:
    template<IS_BASE_OF(GameType, GameBase)>
    void Run();

    template<typename F, typename... Args>
    void CallFuncAfterS(float after, F&& functor, Args&&... args);

    template<typename T, typename F, typename... Args>
    void CallFuncAfterM(float after, T instance, F memfunc, Args&&... args);

    void ReturnMain() noexcept { m_IsPlay = false; }
    void Shutdown() noexcept { m_IsRun = m_IsPlay = false; }

private:
    void Init();
    void Release();
    void MainLoop();
    void GameLoop();

private:
    std::unique_ptr<GameBase>   m_Game;
    std::unique_ptr<Scheduler>  m_Scheduler;
    std::unique_ptr<Timer>      m_Timer;
    bool                        m_IsRun;
    bool                        m_IsPlay;
};

SCE_END
#include "GameManager.inl"
