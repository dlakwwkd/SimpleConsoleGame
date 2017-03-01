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
    // args...는 클로저 안에 전부 복사해서 저장
    // 가변인수를 퍼팩트 포워딩으로 캡쳐하는 기능은 C++14까지는 불가능하다고 함..(17에서 std::apply로 제공 예정)
    // function()의 시그니처에 &&가 있을 경우 이동연산을 지원하기 위해 move로 넘긴다.
    // 즉, args...는 클로저 생성시점에 최소 한번의 복사가 일어난다.( DoTask()에서는 복사없이 람다가 호출될 수 있다.(테스트 완료))
    scheduler->PushTask(_after,
        [functor = std::forward<F>(_functor), _args...]()
        {
            functor(std::move(_args)...);
        });
}

/////////////////////////////////////////////////////////////////////////////////////////
// 멤버함수를 위한 콜펑션
template<typename T, typename F, typename... Args>
void GameManager::CallFuncAfterM(float _after, T* _obj, F _memfunc, Args&& ..._args)
{
    static_assert(std::is_member_function_pointer<F>::value &&
        std::is_same<GameManager, T>::value ||   // 안전성을 위해 게임 매니저와 게임의 멤버함수만 콜펑션을 허락한다.
        std::is_base_of<IGame, T>::value, "only allow GameManager or Game instance");

    scheduler->PushTask(_after, std::bind(_memfunc, _obj, std::forward<Args>(_args)...));
}

/////////////////////////////////////////////////////////////////////////////////////////
// 스마트 포인터로 관리되는 객체의 멤버함수를 위한 콜펑션
template<typename T, typename F, typename... Args>
void GameManager::CallFuncAfterP(float _after, const std::shared_ptr<T>& _obj, F _memfunc, Args&&... _args)
{
    static_assert(std::is_member_function_pointer<F>::value, "only allow member function");
    
    std::weak_ptr<T> objRef = _obj;
    scheduler->PushTask(_after,
        [objRef = std::move(objRef), _memfunc, _args...]()
        {
            // 대상 인스턴스가 살아 있을 때만, 그 멤버함수를 호출해준다.
            if (auto obj = objRef.lock())
            {
                std::bind(_memfunc, obj, std::move(_args)...)();
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
