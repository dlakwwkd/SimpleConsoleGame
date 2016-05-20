SCE_START


template<typename GameType, typename>
void GameManager::Run()
{
    if (m_IsRun || m_Game)
    {
        return;
    }
    m_Game = Safe::New<GameType>();
    if (m_Game)
    {
        Init();
        MainLoop();
        Release();
        Safe::Delete(m_Game);
    }
}

template<typename F, typename... Args>
void GameManager::CallFuncAfter(float after, F&& function, Args&&... args)
{
    m_Scheduler->PushTask(after,
        [function = std::forward<F>(function), args...]()   // args...는 클로저 안에 전부 복사해서 저장
        {                                                   // 가변인수를 퍼팩트 포워딩으로 캡쳐하는 기능은 C++14까지는 불가능하다고 함..(17에서 std::apply로 제공 예정)
            function(std::move(args)...);   // function()의 시그니처에 &&가 있을 경우 이동연산을 지원하기 위해 move로 넘긴다.
        });                                 // 즉, args...는 클로저 생성시점에 최소 한번의 복사가 일어난다.( DoTask()에서는 복사없이 람다가 호출될 수 있다.(테스트 완료))
}

SCE_END
