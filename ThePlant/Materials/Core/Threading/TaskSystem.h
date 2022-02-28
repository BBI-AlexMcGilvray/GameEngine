#pragma once

#include <condition_variable>
#include <mutex>
#include <vector>

#include "TaskQueue.h"
#include "Thread.h"
#include "ThreadManager.h"

namespace Core {
namespace Threading {
// Persistent tasks are not handled by this system, they must be explicitly handled
class TaskSystem
{
public:
    TaskSystem() = default;

    ~TaskSystem();

    void AddThreads(ThreadManager& threadManager, int threadCount);
    void RemoveThreads(ThreadManager& threadManager, int threadCount);

    bool TasksEmpty() const;
    std::future<void> AddTask(std::packaged_task<void()>&& task) const;
    void ClearTasks() const;

    void StopTasks() const;
    void StopAndWaitForTasks() const;
    void CompleteTasks() const;

    void ExecuteTasks();

private:
    mutable std::condition_variable _block;
    TaskQueue _tasks;
    mutable std::vector<Thread> _threads;

    // we want a way to know if tasks are running while also not re-creating threads every frame.
    // may be more performant to have the threads just spin waiting for tasks from the next frame
    mutable std::atomic<bool> _performTasks;

    void _CleanThreads() const;

    void _Execute();
};
} // namespace Threading
} // namespace Core