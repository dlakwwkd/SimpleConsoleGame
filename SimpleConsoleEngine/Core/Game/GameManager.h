﻿#pragma once
SCE_START
class Timer;
class Scheduler;
class Section;
class IRenderObject;
class ICollisionObject;
class IGame;
class Camera;
class Command;

template<typename T>
concept Game = std::derived_from<T, IGame>;

/////////////////////////////////////////////////////////////////////////////////////////
class GameManager
{
    DECLARE_PIMPL
    CREATE_SINGLETON_NOEXCEPT(GameManager)
    using RenderObjPtr      = std::shared_ptr<IRenderObject>;
    using CollisionObjPtr   = std::shared_ptr<ICollisionObject>;
    using SectionPtr        = std::shared_ptr<Section>;
    using SectionRef        = std::weak_ptr<Section>;
    using CameraPtr         = std::unique_ptr<Camera>;
    using CommandPtr        = std::unique_ptr<Command>;
public:
    template<Game T> void       Run();
    template<Game T> T&         GetGame() const;

    template<typename F, typename... Args>
    void                        CallFuncAfterS(float _after, F&& _functor, Args&&... _args);
    template<typename T, typename F, typename... Args>
    void                        CallFuncAfterM(float _after, T* _obj, F _memfunc, Args&&... _args);
    template<typename T, typename F, typename... Args>
    void                        CallFuncAfterP(float _after, const std::shared_ptr<T>& _obj, F _memfunc, Args&&... _args);

    void                        ReturnMain();
    void                        Shutdown();

    void                        AddRender(const RenderObjPtr& _obj, float _lifeTime = -1.f);
    void                        RemoveRender(const RenderObjPtr& _obj);

    void                        RegisterCollision(const CollisionObjPtr& _obj);
    void                        RegisterCollision(const CollisionObjPtr& _obj, const SectionPtr& _trySection);
    void                        UnRegisterCollision(const CollisionObjPtr& _obj);

    void                        RegisterBuiltSection(const SectionPtr& _section, const POINT& _pos);
    SectionPtr                  FindSection(const POINT& _pos) const;

    CameraPtr&                  GetMainCamera();
    CommandPtr&                 GetCommand();
    void                        CommandProc(float dt);

private:
    void                        InitGame();
    void                        ReleaseGame();
    void                        MainLoop();
    void                        GameLoop();

    void                        UpdateProcess();
    void                        RenderProcess();

    float                       FrameProgress();
    void                        SetRenderLimit(size_t _limitFrame);
    bool                        RenderLimitCheck();

    void                        AddCollision(const CollisionObjPtr& _obj);
    void                        RemoveCollision(const CollisionObjPtr& _obj);

    void                        CollisionCheck(float _dt);
    void                        ChangeRenderMode();

    static void                 WindowMain();

private:
    std::unique_ptr<Scheduler>  scheduler;
    std::unique_ptr<Timer>      gameTimer;
    std::unique_ptr<IGame>      curGame;
    bool                        isRun;
    bool                        isPlay;
};

SCE_END
#include "GameManager.inl"
