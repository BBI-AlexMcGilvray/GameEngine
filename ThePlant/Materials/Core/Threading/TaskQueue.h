#pragma once

#include <mutex>
#include <queue>

#include "Thread.h"

namespace Core {
namespace Threading {
class TaskQueue
{
public:
    TaskQueue() = default;
    TaskQueue(TaskQueue&&) = default;
    TaskQueue& operator=(TaskQueue&&) = default;
    ~TaskQueue() = default;

    TaskQueue(const TaskQueue&) = delete;
    TaskQueue& operator=(const TaskQueue&) = delete;

    std::unique_lock<std::mutex> QueueLock() const;

    bool Empty(bool internalLock) const;

    void ClearQueue(std::condition_variable& block) const;
    std::future<void> QueueTask(std::packaged_task<void()>&& task, std::condition_variable& block) const;

    std::packaged_task<void()> ClaimTask(bool internalLock) const;

private:
    mutable std::mutex _mutex;
    mutable std::queue<std::packaged_task<void()>> _tasks;
};
} // namespace Threading
} // namesapce Core