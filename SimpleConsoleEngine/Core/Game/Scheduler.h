#pragma once
SCE_START


class Scheduler
{
    SPECIALFUNC_SET(Scheduler, delete)
    using TickTime = std::chrono::system_clock::time_point;
    using Functor = std::function<void()>;

    struct Task
    {
        TickTime    m_ExecutionTick;
        Functor     m_Task;

        Task(TickTime time, Functor&& task) noexcept;
        bool operator>(const Task& rhs) const noexcept;
    };
    using TaskQueue = std::priority_queue<Task, std::vector<Task>, std::greater<Task>>;

public:
    Scheduler() noexcept;

    void PushTask(float after, Functor&& task) noexcept;
    void DoTask() noexcept;
    void Release() noexcept;

private:
    TaskQueue   m_TaskQueue;
    TickTime    m_CurrentTick;
};

SCE_END
