#include "Core/Threading/ThreadManager.h"

#include <thread>

#include "Core/Logging/Logger.h"
#include "Core/Threading/Thread.h"

namespace Core {
namespace Threading {
bool ThreadManager::_THREAD_MANAGER_CREATED = false; 
ThreadId ThreadManager::_MAIN_THREAD;

ThreadManager::ThreadManager()
: _maxThreads(std::thread::hardware_concurrency())
, _usedThreads(0)
{
    if (_THREAD_MANAGER_CREATED)
    {
        CORE_THROW("ThreadManager", "Thread manager being created twice");
    }

    _THREAD_MANAGER_CREATED = true;
    _MAIN_THREAD = std::this_thread::get_id();
}

ThreadManager::~ThreadManager() // verify all threads are done executing
{
    if (_usedThreads != 0)
    {
        std::abort();
    }
}

uint32_t ThreadManager::MaxThreads() const { return _maxThreads; }
uint32_t ThreadManager::AvailableThreads() const { return _maxThreads - _usedThreads; }

/*
All methods should verify that they are being called from the main thread
This class should only me accessible from the main thread (avoid hidden work explosion)
*/
Thread ThreadManager::GetThread()
{
    if (std::this_thread::get_id() != _MAIN_THREAD)
    {
        CORE_THROW("ThreadManager", "Getting thread from not the main thread");
    }

    if (_usedThreads > _maxThreads)
    {
        throw std::range_error("more threads gotten than exist");
    }

    ++_usedThreads;
    return Thread(*this);
}

// we Thread&& required to enforce that the thread is properly returned
void ThreadManager::ReturnThread(Thread&& thread)
{
    if (std::this_thread::get_id() != _MAIN_THREAD)
    {
        CORE_THROW("ThreadManager", "Getting thread from not the main thread");
    }

    --_usedThreads;
    if (_usedThreads > _maxThreads)
    {
        throw std::range_error("more threads returned than exist");
    }
}
} // namespace Threading
} // namespace Core