#include "Scheduler.h"
SCE_START

/////////////////////////////////////////////////////////////////////////////////////////
CHECKED_T(T)
void GameManager::Run()
{
    if (isRun || curGame)
    {
        return;
    }
    curGame = std::make_unique<T>();
    if (curGame)
    {
        InitGame();
        MainLoop();
        ReleaseGame();
        curGame.reset();
    }
}

/////////////////////////////////////////////////////////////////////////////////////////
CHECKED_T(T)
T& GameManager::GetGame() const
{
    return dynamic_cast<T&>(*curGame);
}

/////////////////////////////////////////////////////////////////////////////////////////
// 람다와 전역함수를 위한 콜펑션
template<typename F, typename... Args>
void GameManager::CallFuncAfterS(float _after, F&& _functor, Args&&... _args)
{
    static_assert(!std::is_member_function_pointer_v<F>, "only allow non member function");

    scheduler->PushTask(_after,
        std::bind(std::forward<F>(_functor), std::forward<Args>(_args)...));
}

/////////////////////////////////////////////////////////////////////////////////////////
// 멤버함수를 위한 콜펑션
template<typename T, typename F, typename... Args>
void GameManager::CallFuncAfterM(float _after, T* _obj, F _memfunc, Args&& ..._args)
{
    // 안전성을 위해 게임 매니저와 게임의 멤버함수만 콜펑션을 허락한다.
    static_assert(std::is_member_function_pointer_v<F> &&
        (std::is_same_v<GameManager, T> || std::is_base_of_v<IGame, T>),
        "only allow GameManager or Game instance");

    scheduler->PushTask(_after,
        std::bind(_memfunc, _obj, std::forward<Args>(_args)...));
}

/////////////////////////////////////////////////////////////////////////////////////////
// 스마트 포인터로 관리되는 객체의 멤버함수를 위한 콜펑션
template<typename T, typename F, typename... Args>
void GameManager::CallFuncAfterP(float _after, const std::shared_ptr<T>& _obj, F _memfunc, Args&&... _args)
{
    static_assert(std::is_member_function_pointer_v<F>, "only allow member function");
    
    std::weak_ptr<T> objRef = _obj;
    scheduler->PushTask(_after,
        [objRef = std::move(objRef), _memfunc, _args...]()
        {
            // 대상 인스턴스가 살아 있을 때만, 그 멤버함수를 호출해준다.
            if (auto obj = objRef.lock())
            {
                std::invoke(_memfunc, obj.get(), std::move(_args)...);
            }
        });
}

SCE_END

/////////////////////////////////////////////////////////////////////////////////////////
// for SectionMap key
inline bool operator<(const POINT& _l, const POINT& _r)
{
    return _l.x < _r.x || (_l.x == _r.x && _l.y < _r.y);
}
