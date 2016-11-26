#include "stdafx.h"
#include "Scheduler.h"
SCE_START



Scheduler::Task::Task(TickTime _time, Functor&& _func) noexcept
    : executionTick(_time)
    , function(std::move(_func))
{
}


bool Scheduler::Task::operator>(const Task& _rhs) const noexcept
{
    return executionTick > _rhs.executionTick;
}


Scheduler::Scheduler() noexcept
    : curTick(std::chrono::system_clock::now())
{
}


void Scheduler::PushTask(float _after, Functor&& _func) noexcept
{
    TickTime dueTimeTick = curTick + std::chrono::milliseconds(static_cast<int64_t>(_after * 1000.0f));
    taskQueue.emplace(dueTimeTick, std::move(_func));
}

void Scheduler::DoTask() noexcept
{
    curTick = std::chrono::system_clock::now();
    while (!taskQueue.empty())
    {
        const Task& task = taskQueue.top();
        if (curTick < task.executionTick)
        {
            break;
        }
        task.function();
        taskQueue.pop();
    }
}

void Scheduler::Release() noexcept
{
    while (!taskQueue.empty())
    {
        taskQueue.pop();
    }
}

SCE_END
