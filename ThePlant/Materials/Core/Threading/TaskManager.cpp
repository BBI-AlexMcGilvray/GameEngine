#include "Core/Threading/TaskManager.h"

#include "Core/Logging/Logger.h"

namespace Core {
namespace Threading {
TaskManager::~TaskManager()
{
    StopAllTasks();
    ClearAllTasks();
    CompleteAllTasks();
}

void TaskManager::AddThreads(TaskWeight taskWeight, ThreadManager& threadManager, int threadCount)
{
    switch (taskWeight)
    {
        case TaskWeight::Light:
        {
            return _lightTasks.AddThreads(threadManager, threadCount);
        }
        case TaskWeight::Heavy:
        {
            return _heavyTasks.AddThreads(threadManager, threadCount);
        }
    }
    
    CORE_THROW("TaskManager", "Invalid weight provided");
}

void TaskManager::RemoveThreads(TaskWeight taskWeight, ThreadManager& threadManager, int threadCount)
{
    switch (taskWeight)
    {
        case TaskWeight::Light:
        {
            return _lightTasks.RemoveThreads(threadManager, threadCount);
        }
        case TaskWeight::Heavy:
        {
            return _heavyTasks.RemoveThreads(threadManager, threadCount);
        }
    }

    CORE_THROW("TaskManager", "Invalid weight provided");
}

bool TaskManager::AllTasksEmpty() const
{
    return TasksEmpty(TaskWeight::Light) && TasksEmpty(TaskWeight::Heavy);
}

bool TaskManager::TasksEmpty(TaskWeight taskWeight) const
{
    switch (taskWeight)
    {
        case TaskWeight::Light:
        {
            return _lightTasks.TasksEmpty();
        }
        case TaskWeight::Heavy:
        {
            return _heavyTasks.TasksEmpty();
        }
    }

    CORE_THROW("TaskManager", "Invalid weight provided");
}

std::future<void> TaskManager::AddTask(TaskWeight taskWeight, std::packaged_task<void()>&& task) const
{
    switch (taskWeight)
    {
        case TaskWeight::Light:
        {
            return _lightTasks.AddTask(std::move(task));
        }
        case TaskWeight::Heavy:
        {
            return _heavyTasks.AddTask(std::move(task));
        }
    }

    CORE_THROW("TaskManager", "Invalid weight provided");
}

void TaskManager::ClearAllTasks() const
{
    ClearTasks(TaskWeight::Light);
    ClearTasks(TaskWeight::Heavy);
}

void TaskManager::ClearTasks(TaskWeight taskWeight) const
{
    switch (taskWeight)
    {
        case TaskWeight::Light:
        {
            _lightTasks.ClearTasks();
            return;
        }
        case TaskWeight::Heavy:
        {
            _heavyTasks.ClearTasks();
            return;
        }
    }

    CORE_THROW("TaskManager", "Invalid weight provided");
}

void TaskManager::StopAllTasks() const
{
    StopTasks(TaskWeight::Light);
    StopTasks(TaskWeight::Heavy);
}

void TaskManager::StopTasks(TaskWeight taskWeight) const
{
    switch (taskWeight)
    {
        case TaskWeight::Light:
        {
            _lightTasks.StopTasks();
            return;
        }
        case TaskWeight::Heavy:
        {
            _heavyTasks.StopTasks();
            return;
        }
    }
    
    CORE_THROW("TaskManager", "Invalid weight provided");
}

void TaskManager::StopAndCompleteAllTasks() const
{
    StopAllTasks();
    CompleteAllTasks();
}

// calling without calling the respective stop will result in an infinite wait
void TaskManager::CompleteAllTasks() const
{
    CompleteTasks(TaskWeight::Light);
    CompleteTasks(TaskWeight::Heavy);
}

// calling without calling the respective stop will result in an infinite wait
void TaskManager::CompleteTasks(TaskWeight taskWeight) const
{
    switch (taskWeight)
    {
        case TaskWeight::Light:
        {
            _lightTasks.CompleteTasks();
            return;
        }
        case TaskWeight::Heavy:
        {
            _heavyTasks.CompleteTasks();
            return;
        }
    }

    CORE_THROW("TaskManager", "Invalid weight provided");
}

void TaskManager::ExecuteAllTasks()
{
    ExecuteTasks(TaskWeight::Light);
    ExecuteTasks(TaskWeight::Heavy);
}

void TaskManager::ExecuteTasks(TaskWeight taskWeight)
{
    switch (taskWeight)
    {
        case TaskWeight::Light:
        {
            _lightTasks.ExecuteTasks();
            return;
        }
        case TaskWeight::Heavy:
        {
            _heavyTasks.ExecuteTasks();
            return;
        }
    }

    CORE_THROW("TaskManager", "Invalid weight provided");
}
} // namespace Threading
} // namespace Core