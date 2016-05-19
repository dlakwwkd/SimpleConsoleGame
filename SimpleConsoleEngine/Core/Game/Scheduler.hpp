#pragma once
SCE_START


class Scheduler
{
    CREATE_SINGLETON(Scheduler)
public:
    template<typename F, typename... Args>
    void PushTask(float after, F&& function, Args&&... args)
    {
        auto dueTimeTick = m_CurrentTick + std::chrono::milliseconds(static_cast<int64_t>(after * 1000.0f));
        m_TaskQueue.push(Task([function, args...](){ function(args...); }, dueTimeTick));
    }

    void DoTask()
    {
        m_CurrentTick = std::chrono::system_clock::now();
        while (!m_TaskQueue.empty())
        {
            Task task = m_TaskQueue.top();
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
    using TickTime  = std::chrono::system_clock::time_point;

    struct Task
    {
        std::function<void()>   m_Task;
        TickTime                m_ExecutionTick;

        Task(std::function<void()>&& task, TickTime&& time)
        :   m_Task(std::move(task)),
            m_ExecutionTick(std::move(time))
        {
        }
        bool operator > (const Task& rhs) const noexcept { return m_ExecutionTick > rhs.m_ExecutionTick; }
    };
    using TaskQueue = std::priority_queue<Task, std::vector<Task>, std::greater<Task>>;

    TaskQueue   m_TaskQueue;
    TickTime    m_CurrentTick;
};

#ifdef SIMPLECONSOLEENGINE_EXPORTS
Scheduler::Scheduler() : m_CurrentTick(std::chrono::system_clock::now()) {}
Scheduler::~Scheduler(){}
#endif

SCE_END
