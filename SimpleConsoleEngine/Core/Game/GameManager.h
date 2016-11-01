#pragma once
#include "Scheduler.h"
SCE_START
class IGameBase;
class Timer;
class GameObject;


class GameManager
{
    CREATE_SINGLETON(GameManager)
public:
    IS_BASE_OF(GameType, IGameBase)
    void        Run();
    
    IS_BASE_OF(GameType, IGameBase)
    GameType&   GetGame() const;

    template<typename F, typename... Args>
    void        CallFuncAfterS(float after, F&& functor, Args&&... args);

    template<typename T, typename F, typename... Args>
    void        CallFuncAfterM(float after, T* pObj, F memfunc, Args&&... args);

    template<typename T, typename F, typename... Args>
    void        CallFuncAfterP(float after, const std::shared_ptr<T>& pObj, F memfunc, Args&&... args);

    void        ReturnMain();
    void        Shutdown();

private:
    void        InitGame();
    void        ReleaseGame();
    void        MainLoop();
    void        GameLoop();

    void        UpdateProcess();
    void        RenderProcess();

    float       FrameProgress();
    void        SetRenderLimit(size_t limitFrame);
    bool        RenderLimitCheck();
    void        PrintFrame();

private:
    std::unique_ptr<Scheduler>  m_Scheduler;
    std::unique_ptr<IGameBase>  m_Game;
    std::unique_ptr<Timer>      m_Timer;
    bool                        m_IsRun;
    bool                        m_IsPlay;
    size_t                      m_FrameCount;
    size_t                      m_RenderCount;
    size_t                      m_RenderLimit;
};

SCE_END
#include "GameManager.inl"
