#pragma once
SCE_START

/////////////////////////////////////////////////////////////////////////////////////////
class Scheduler
{
    SPECIALFUNC_SET(Scheduler, delete)
    using TickTime = std::chrono::system_clock::time_point;
    using Functor = std::function<void()>;

    /////////////////////////////////////////////////////////////////////////////////////
    struct Task
    {
        TickTime    executionTick;
        Functor     function;

        Task(TickTime _time, Functor&& _func) noexcept;
        bool operator>(const Task& _rhs) const noexcept;
    };
    using TaskQueue = std::priority_queue<Task, std::vector<Task>, std::greater<Task>>;

public:
    Scheduler() noexcept;

    void        PushTask(float _after, Functor&& _func) noexcept;
    void        DoTask() noexcept;
    void        Release() noexcept;

private:
    TaskQueue   taskQueue;
    TickTime    curTick;
};

SCE_END
