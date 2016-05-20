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

        Task(TickTime time, Functor&& task) noexcept
        :   m_ExecutionTick(time),
            m_Task(std::move(task))
        {
        }
        bool operator > (const Task& rhs) const noexcept { return m_ExecutionTick > rhs.m_ExecutionTick; }
    };
    using TaskQueue = std::priority_queue<Task, std::vector<Task>, std::greater<Task>>;

public:
    Scheduler() : m_CurrentTick(std::chrono::system_clock::now())
    {
    }

    void PushTask(float after, Functor&& task)
    {
        TickTime dueTimeTick = m_CurrentTick + std::chrono::milliseconds(static_cast<int64_t>(after * 1000.0f));
        m_TaskQueue.emplace(Task(dueTimeTick, std::move(task)));
    }

    void DoTask()
    {
        m_CurrentTick = std::chrono::system_clock::now();
        while (!m_TaskQueue.empty())
        {
            const Task& task = m_TaskQueue.top();
            if (m_CurrentTick < task.m_ExecutionTick)
            {
                break;
            }
            task.m_Task();
            m_TaskQueue.pop();
        }
    }

    void Release()
    {
        while (!m_TaskQueue.empty())
        {
            m_TaskQueue.pop();
        }
    }

private:
    TaskQueue   m_TaskQueue;
    TickTime    m_CurrentTick;
};

SCE_END
