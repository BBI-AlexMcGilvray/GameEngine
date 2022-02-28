#pragma once

#include <mutex>

#include "TaskSystem.h"
#include "TaskQueue.h"
#include "Thread.h"
#include "ThreadManager.h"

// Persistent tasks are not handled by this system, they must be explicitly handled
namespace Core {
namespace Threading {
enum class TaskWeight
{
    Unknown,
    Light,
    Heavy,
    Persistent
};

class TaskManager
{
public:
    TaskManager() = default;

    ~TaskManager();
    
    void AddThreads(TaskWeight taskWeight, ThreadManager& threadManager, int threadCount);
    void RemoveThreads(TaskWeight taskWeight, ThreadManager& threadManager, int threadCount);

    bool AllTasksEmpty() const;
    bool TasksEmpty(TaskWeight taskWeight) const;

    std::future<void> AddTask(TaskWeight taskWeight, std::packaged_task<void()>&& task) const;
    void ClearAllTasks() const;
    void ClearTasks(TaskWeight taskWeight) const;

    void StopAllTasks() const;
    void StopTasks(TaskWeight taskWeight) const;
    void StopAndCompleteAllTasks() const;
    // calling without calling the respective stop will result in an infinite wait
    void CompleteAllTasks() const;
    // calling without calling the respective stop will result in an infinite wait
    void CompleteTasks(TaskWeight taskWeight) const;

    void ExecuteAllTasks();
    void ExecuteTasks(TaskWeight taskWeight);

private:
    TaskSystem _lightTasks;
    TaskSystem _heavyTasks;
};
} // namespace Threading
} // namesapce Core