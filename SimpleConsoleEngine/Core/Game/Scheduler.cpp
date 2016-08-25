#include "stdafx.h"
#include "Scheduler.h"
SCE_START



Scheduler::Task::Task(TickTime time, Functor&& task)
:   m_ExecutionTick(time),
    m_Task(std::move(task))
{
}


bool Scheduler::Task::operator>(const Task& rhs) const
{
    return m_ExecutionTick > rhs.m_ExecutionTick;
}



Scheduler::Scheduler()
:   m_CurrentTick(std::chrono::system_clock::now())
{
}


void Scheduler::PushTask(float after, Functor&& task)
{
    TickTime dueTimeTick = m_CurrentTick + std::chrono::milliseconds(static_cast<int64_t>(after * 1000.0f));
    m_TaskQueue.emplace(Task(dueTimeTick, std::move(task)));
}

void Scheduler::DoTask()
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

void Scheduler::Release()
{
    while (!m_TaskQueue.empty())
    {
        m_TaskQueue.pop();
    }
}

SCE_END
