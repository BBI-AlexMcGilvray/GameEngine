#include "Thread.h"

#include "Core/Logging/LogFunctions.h"

namespace Core {
namespace Threading {
Thread::Thread(const ThreadManager& necessary)
: _validThread(true)
{}

Thread::Thread(Thread&& other)
{
    *this = std::move(other);
}

Thread& Thread::operator=(Thread&& other)
{
    auto otherLock = other._ThreadLock();
    other.Complete(); // maybe do an assert if other is running? threads should never be moved when active

    _validThread = std::move(other._validThread);
    _task = std::move(other._task);
    _executed = false; // other._executed should always be false - consider verifying

    return *this;
}

Thread::~Thread()
{
    Complete();
}

// function return true if it should be run again
void Thread::Clean()
{
    SetTask(std::packaged_task<void()>());
}

std::future<void> Thread::SetTask(std::packaged_task<void()>&& task)
{
    auto lock = _ThreadLock();
    _MustBeValidThread();

    _task = std::move(task);
    return _task.valid() ? _task.get_future() : std::future<void>();
}

std::future<void> Thread::SetTaskAndRun(std::packaged_task<void()>&& task)
{
    auto lock = _ThreadLock();
    
    auto future = SetTask(std::move(task));
    Run();

    return future;
}

void Thread::Run()
{
    _thread = std::thread(&Thread::_Run, this);
}

void Thread::Complete()
{
    auto lock = _ThreadLock();
    if (Completeable())
    {
        _thread.join();
    }

    Clean(); // all tasks must be 'Wait'-ed at some point, so clean here instead of at the end of '_Run'
    _executed = false;
}

bool Thread::Completeable() const
{
    _MustBeValidThread();
    return _thread.joinable();
}

ThreadId Thread::GetId() const
{
    return _thread.get_id();
}

std::unique_lock<std::recursive_mutex> Thread::_ThreadLock() const
{
    return std::unique_lock(_mutex);
}

void Thread::_MustBeValidThread() const
{
    if (!_validThread)
    {
        CORE_THROW("Thread", "Thread is not valid!");
    }
}

void Thread::_Run()
{
    auto lock = _ThreadLock();
    if (_task.valid())
    {
        // copy to avoid any issues with calling clean while executing
        std::packaged_task<void()> taskCopy = std::move(_task);
        _executed = true;
        lock.unlock();
        taskCopy();
    }
    else
    {
        CORE_THROW("Thread", "Trying to execute an invalid task");
    }
}

bool IsFinished(const std::future<void>& future)
{
    // if this is slow, apparently using wait_until(steady_clock.now()) is faster, but would want to provide a clock for that instead of creating a new one
    return future.wait_for(std::chrono::seconds(0)) == std::future_status::ready;
}
} // namespace Threading
} // namespace Core