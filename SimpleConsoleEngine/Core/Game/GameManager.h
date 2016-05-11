﻿#pragma once
SCE_START
class IGame;
class Timer;


class SCE_API GameManager
{
    CREATE_SINGLETON(GameManager)
public:
    template<typename GameType>
    inline void Run();

    inline void ReturnMain() noexcept { m_IsPlay = false; }
    inline void Shutdown() noexcept { m_IsRun = m_IsPlay = false; }

private:
    void Init();
    void Release();
    void MainLoop();
    void GameLoop();

private:
    IGame*  m_Game;
    Timer*  m_Timer;
    bool    m_IsRun;
    bool    m_IsPlay;
};

SCE_END
#include "GameManager.inl"