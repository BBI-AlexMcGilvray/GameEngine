#pragma once

#include <functional>
#include <future>
#include <mutex>
#include <thread>

namespace Core {
namespace Threading {
class ThreadManager;

using ThreadId = std::thread::id;

class Thread
{
public:
    Thread() // only threads made by the ThreadManager are valid
    : _validThread(false)
    {}

    Thread(Thread&& other);
    Thread& operator=(Thread&& other);

    ~Thread();

    Thread(const Thread& other) = delete;
    Thread& operator=(const Thread&) = delete;

    ThreadId GetId() const;

    // functions returns if it should stop being run (true = stop)
    void Clean();
    std::future<void> SetTask(std::packaged_task<void()>&& task);
    std::future<void> SetTaskAndRun(std::packaged_task<void()>&& task);
    void Run();
    void Complete();
    bool Completeable() const;

    // explicitly no detach method, seems like a good way to shoot ourselves in the foot

private:
    friend class ThreadManager;
    Thread(const ThreadManager& necessary);

    mutable std::recursive_mutex _mutex;
    std::packaged_task<void()> _task;

    bool _validThread;
    mutable bool _executed;
    mutable std::thread _thread;

    std::unique_lock<std::recursive_mutex> _ThreadLock() const;
    void _MustBeValidThread() const;

    void _Run();
};

bool IsFinished(const std::future<void>& future);
} // namespace Threading
} // namespace Core