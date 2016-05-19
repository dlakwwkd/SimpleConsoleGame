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

    void ReturnMain() noexcept { m_IsPlay = false; }
    void Shutdown() noexcept { m_IsRun = m_IsPlay = false; }

    template<typename F, typename... Args>
    void CallFuncAfter(float after, F&& function, Args&&... args)
    {
        static auto& scheduler = Scheduler::GetInstance();
        scheduler.PushTask(after, std::forward<F>(function), std::forward<Args>(args)...);
    }

private:
    void Init();
    void Release();
    void MainLoop();
    void GameLoop();

private:
    GameBase*   m_Game;
    Timer*      m_Timer;
    bool        m_IsRun;
    bool        m_IsPlay;
};

SCE_END
#include "GameManager.inl"
