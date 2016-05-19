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

SCE_END
