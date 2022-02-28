#pragma once

#include "Core/Threading/Thread.h"

namespace Core {
namespace Threading {
// no point in having this actually hold threads, as threads are only moveable
// instead just ensure we never go above a certain amount
class ThreadManager
{
public:
    ThreadManager();
    ~ThreadManager();

    ThreadManager(ThreadManager&&) = delete;
    ThreadManager(const ThreadManager&) = delete;
    ThreadManager& operator=(ThreadManager&&) = delete;
    ThreadManager& operator=(const ThreadManager&) = delete;

    uint32_t MaxThreads() const;
    uint32_t AvailableThreads() const;

    Thread GetThread();
    // Thread&& required to enforce that the thread is properly returned
    void ReturnThread(Thread&& thread);

private:
    static bool _THREAD_MANAGER_CREATED;
    static ThreadId _MAIN_THREAD;

    uint32_t _maxThreads;
    uint32_t _usedThreads;
};
} // namespace Threading
} // namespace Core