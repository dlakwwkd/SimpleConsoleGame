SCE_START


CHECKED_T(GameType)
void GameManager::Run()
{
    if (m_IsRun || m_Game)
    {
        return;
    }
    m_Game = std::make_unique<GameType>();
    if (m_Game)
    {
        InitGame();
        MainLoop();
        ReleaseGame();
        m_Game.reset();
    }
}

CHECKED_T(GameType)
GameType& GameManager::GetGame() const
{
    return dynamic_cast<GameType&>(*m_Game);
}

// 람다와 전역함수를 위한 콜펑션
template<typename F, typename... Args>
void GameManager::CallFuncAfterS(float after, F&& functor, Args&&... args)
{
    m_Scheduler->PushTask(after,
        [functor = std::forward<F>(functor), args...]() // args...는 클로저 안에 전부 복사해서 저장
        {                                               // 가변인수를 퍼팩트 포워딩으로 캡쳐하는 기능은 C++14까지는 불가능하다고 함..(17에서 std::apply로 제공 예정)
            functor(std::move(args)...);    // function()의 시그니처에 &&가 있을 경우 이동연산을 지원하기 위해 move로 넘긴다.
        });                                 // 즉, args...는 클로저 생성시점에 최소 한번의 복사가 일어난다.( DoTask()에서는 복사없이 람다가 호출될 수 있다.(테스트 완료))
}

// 멤버함수를 위한 콜펑션
template<typename T, typename F, typename... Args>
void GameManager::CallFuncAfterM(float after, T* pObj, F memfunc, Args&& ...args)
{
    static_assert(std::is_member_function_pointer<F>::value &&
        std::is_same<GameManager, T>::value ||   // 안전성을 위해 게임 매니저와 게임의 멤버함수만 콜펑션을 허락한다.
        std::is_base_of<IGameBase, T>::value, "only allow GameManager or Game instance");

    m_Scheduler->PushTask(after, std::bind(memfunc, pObj, std::forward<Args>(args)...));
}

// 스마트 포인터로 관리되는 객체의 멤버함수를 위한 콜펑션
template<typename T, typename F, typename... Args>
void GameManager::CallFuncAfterP(float after, const std::shared_ptr<T>& pObj, F memfunc, Args&&... args)
{
    static_assert(std::is_member_function_pointer<F>::value, "only allow member function");
    
    std::weak_ptr<T> refObj = pObj;
    m_Scheduler->PushTask(after,
        [refObj = std::move(refObj), memfunc, args...]()
        {
            // 대상 인스턴스가 살아 있을 때만, 그 멤버함수를 호출해준다.
            if (auto pObj = refObj.lock())
            {
                std::bind(memfunc, pObj, std::move(args)...)();
            }
        });
}

SCE_END
