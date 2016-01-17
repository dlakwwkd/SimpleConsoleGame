#pragma once
class Timer;

class GameManager
{
public:
    static GameManager* GetInstance()
    {
        static GameManager instance;
        return &instance;
    }
    void Init();
    void Release();

    void Run();
    void GameLoop();

    void Update(float dt);
    void Render();
private:
    GameManager();
    ~GameManager();

    std::unique_ptr<Timer>  m_Timer;
    bool                    m_IsGameRun;
};
