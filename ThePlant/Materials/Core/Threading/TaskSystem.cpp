#include "Core/Threading/TaskSystem.h"

namespace Core {
namespace Threading {
TaskSystem::~TaskSystem()
{
    StopTasks();
    ClearTasks();
    CompleteTasks();
}

void TaskSystem::AddThreads(ThreadManager& threadManager, int threadCount)
{
    for (int i = 0; i < threadCount; ++i)
    {
        _threads.emplace_back(threadManager.GetThread());
    }
}

void TaskSystem::RemoveThreads(ThreadManager& threadManager, int threadCount)
{
    for (int i = 0; i < threadCount; ++i)
    {
        size_t lastIndex = _threads.size() - 1;

        Thread thread = std::move(_threads[lastIndex]);

        _threads.erase(_threads.begin() + lastIndex);
        threadManager.ReturnThread(std::move(thread));
    }
}

bool TaskSystem::TasksEmpty() const
{
    return _tasks.Empty(true);
}

std::future<void> TaskSystem::AddTask(std::packaged_task<void()>&& task) const
{
    return _tasks.QueueTask(std::move(task), _block);
}

void TaskSystem::ClearTasks() const
{
    _tasks.ClearQueue(_block);
}

void TaskSystem::StopTasks() const
{
    _performTasks = false;
    _block.notify_all();

    _CleanThreads();
}

void TaskSystem::StopAndWaitForTasks() const
{
    StopTasks();
    CompleteTasks();
}

void TaskSystem::CompleteTasks() const
{
    for (auto& thread : _threads)
    {
        thread.Complete();
    }
}

void TaskSystem::ExecuteTasks()
{
    _performTasks = true;

    for (auto& thread : _threads)
    {
        thread.SetTaskAndRun(std::packaged_task<void()>(std::bind(&TaskSystem::_Execute, this)));
    }
}

void TaskSystem::_CleanThreads() const
{
    for (auto& thread : _threads)
    {
        thread.Clean();
    }
}

void TaskSystem::_Execute()
{
    while (_performTasks.load())
    {
        auto lock = _tasks.QueueLock();
        _block.wait(lock, [this]{
            return !_tasks.Empty(false) || !_performTasks;
        });
        if (!_tasks.Empty(false) && _performTasks.load())
        {
            auto task = _tasks.ClaimTask(false);
            lock.unlock();

            task();
        }
    }
}
} // namespace Threading
} // namespace Core