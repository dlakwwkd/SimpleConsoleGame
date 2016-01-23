#pragma once
class Timer;
class GameBase;

using TimerPtr  = std::unique_ptr<Timer>;
using GamePtr   = std::shared_ptr<GameBase>;
using GameList  = std::vector<GamePtr>;

class GameManager
{
public:
    static GameManager* GetInstance()
    {
        static GameManager instance;
        return &instance;
    }
    void Run();
    void Play();

    void ReturnMain() { m_IsPlay = false; }
    void Shutdown() { m_IsRun = false; }

private:
    TimerPtr    m_Timer;
    GameList    m_GameList;
    GamePtr     m_CurGame;
    bool        m_IsRun;
    bool        m_IsPlay;

private:
    GameManager();
    ~GameManager();

    void Init();
    void Release();

    void MainLoop();
    void GameLoop();

    void GameSelect();
};
