#include "Core/Debugging/Profiling/Profiler.h"

#include "Core/Debugging/Memory/MemoryTrackerUtils.h"
#include "Core/Logging/LogFunctions.h"

namespace Core {
namespace Profiling
{
#if DEBUG
void Profiler::Push(const std::string& tag)
{    
    SCOPED_MEMORY_CATEGORY("Profiler");

    auto lock = _LockStacks();
    auto thisThread = std::this_thread::get_id();
    auto& thisStack = _threadStacks[thisThread];
    lock.unlock();

    if (!collectData)
    {
        thisStack = std::stack<Section>(); // not collecting data, clear this thread
        return;
    }

    thisStack.push(Section(tag, _clock));
}

void Profiler::Pop(const std::string& tag)
{
    SCOPED_MEMORY_CATEGORY("Profiler");
    auto lock = _LockStacks();
    auto thisThread = std::this_thread::get_id();
    auto& thisStack = _threadStacks[thisThread];
    lock.unlock();

    if (thisStack.empty())
    {
        // can't error here if collectData == true because it is threaded and could be false positive
        return;
    }

    Section popped = thisStack.top();
    popped.end = _clock.now();

    if (popped.tag != tag)
    {
        CORE_THROW("Profiler", "Improper stacking push/pop sequence! " + tag + " != " + popped.tag);
    }
    thisStack.pop();

    if (thisStack.empty())
    {
        _AddThreadSection(thisThread, std::move(popped));
    }
    else
    {
        thisStack.top().sections.push_back(popped);
    }
}

const std::unordered_map<Threading::ThreadId, std::vector<Section>> Profiler::GetThreadSections() const
{
    auto lock = _LockSections();
    return _threadSections;
}

const std::unordered_map<Threading::ThreadId, std::vector<Section>> Profiler::GetThreadSectionsThenClear()
{
    SCOPED_MEMORY_CATEGORY("Profiler");
    auto lock = _LockSections();
    std::unordered_map<Threading::ThreadId, std::vector<Section>> threadSections = _threadSections;
    _threadSections.clear();

    return threadSections;
}

void Profiler::ClearSections()
{
    auto lock = _LockSections();
    _threadSections.clear();
}

std::unique_lock<std::mutex> Profiler::_LockSections() const
{
    return std::unique_lock(_sectionMutex);
}

std::unique_lock<std::mutex> Profiler::_LockStacks() const
{
    return std::unique_lock(_stackMutex);
}

void Profiler::_AddThreadSection(Threading::ThreadId thread, Section&& section)
{
    SCOPED_MEMORY_CATEGORY("Profiler");
    auto lock = _LockSections();
    _threadSections[thread].emplace_back(std::move(section));
}
#endif
} // namespace Profiling
}// namespace Core