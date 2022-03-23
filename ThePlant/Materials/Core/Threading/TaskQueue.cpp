#include "Core/Threading/TaskQueue.h"

#include "Core/Debugging/Memory/MemoryTrackerUtils.h"

namespace Core {
namespace Threading {
std::unique_lock<std::mutex> TaskQueue::QueueLock() const
{
    return std::unique_lock(_mutex);
}

bool TaskQueue::Empty(bool internalLock) const
{
    auto lock = internalLock ? QueueLock() : std::unique_lock<std::mutex>();
    bool empty = _tasks.empty();
    if (internalLock)
    {
        lock.unlock();
    }

    return empty;
}

void TaskQueue::ClearQueue(std::condition_variable& block) const
{
    auto lock = QueueLock();
    while (!_tasks.empty())
    {
        _tasks.front().reset();
        _tasks.pop();
    }
    block.notify_all();
}

std::future<void> TaskQueue::QueueTask(std::packaged_task<void()>&& task, std::condition_variable& block) const
{
    SCOPED_MEMORY_CATEGORY("Threading");
    auto lock = QueueLock();
    _tasks.push(std::move(task));
    std::future<void> handle = _tasks.back().get_future();
    lock.unlock();

    block.notify_one();
    return handle;
}

std::packaged_task<void()> TaskQueue::ClaimTask(bool internalLock) const
{
    auto lock = internalLock ? QueueLock() : std::unique_lock<std::mutex>();
    std::packaged_task<void()> nextTask = std::move(_tasks.front());
    _tasks.pop();
    if (internalLock)
    {
        lock.unlock();
    }

    return std::move(nextTask);
}
} // namespace Threading
} // namespace Core