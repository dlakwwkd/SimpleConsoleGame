#pragma once
SCE_START
class Scheduler;
class IGameBase;
class Timer;
class IRender;
class ICollision;
class Section;


class GameManager
{
    CREATE_SINGLETON_NOEXCEPT(GameManager)
    using RenderPtr     = std::shared_ptr<IRender>;
    using CollisionPtr  = std::shared_ptr<ICollision>;
    using SectionPtr    = std::shared_ptr<Section>;
    using SectionRef    = std::weak_ptr<Section>;
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

    void        AddRender(const RenderPtr& obj, float lifeTime = -1.f);
    void        RemoveRender(const RenderPtr& obj);

    void        AddCollision(const CollisionPtr& obj);
    void        RemoveCollision(const CollisionPtr& obj);

    void        RegisterCollision(const CollisionPtr& obj);
    void        RegisterCollision(const CollisionPtr& obj, const SectionPtr& trySection);
    void        UnRegisterCollision(const CollisionPtr& obj);

    void        RegisterBuiltSection(const SectionPtr& section, const POINT& pos);
    SectionPtr  FindSection(const POINT& pos) const;

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

    void        CollisionCheck(float dt);
    void        SectionNumPrint() const;

private:
    std::unique_ptr<Scheduler>  m_Scheduler;
    std::unique_ptr<IGameBase>  m_Game;
    std::unique_ptr<Timer>      m_Timer;

    bool                        m_IsRun;
    bool                        m_IsPlay;
    size_t                      m_FrameCount;
    size_t                      m_RenderCount;
    size_t                      m_RenderLimit;

    std::list<RenderPtr>        m_RenderList;
    std::list<CollisionPtr>     m_CollisionList;
    std::vector<SectionPtr>     m_SectionList;
    std::map<POINT, SectionRef> m_SectionMap;
    SectionPtr                  m_RootSection;

    friend bool operator<(const POINT& l, const POINT& r)
    {
        return l.x < r.x || (l.x == r.x && l.y < r.y);
    }
};

SCE_END
#include "GameManager.inl"
