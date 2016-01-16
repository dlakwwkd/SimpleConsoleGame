#pragma once
class Timer
{
public:
    static Timer* GetInstance()
    {
        static Timer instance;
        return &instance;
    }
private:
    Timer();
    ~Timer();
};

