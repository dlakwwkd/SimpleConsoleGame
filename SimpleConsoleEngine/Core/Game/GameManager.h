#pragma once
#include "Scheduler.hpp"
SCE_START
class GameBase;
class Timer;


class SCE_API GameManager
{
    CREATE_SINGLETON(GameManager)
public:
    template<typename GameType, BASETYPE_CHECK(GameType, GameBase)>
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
    GameBase*   m_Game;
    Scheduler*  m_Scheduler;
    Timer*      m_Timer;
    bool        m_IsRun;
    bool        m_IsPlay;
};

SCE_END
#include "GameManager.inl"
