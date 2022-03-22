#include "Core/Debugging/Profiling/Profiler.h"
#include "Core/Logging/LogFunctions.h"

namespace Core {
namespace Profiling
{
#if DEBUG
void Profiler::Push(const std::string& tag)
{
    auto lock = _LockStacks();
    auto thisThread = std::this_thread::get_id();
    auto& thisStack = _threadStacks[thisThread];
    lock.unlock();

    thisStack.push(Section(tag, _clock));
}

void Profiler::Pop(const std::string& tag)
{
    auto lock = _LockStacks();
    auto thisThread = std::this_thread::get_id();
    auto& thisStack = _threadStacks[thisThread];
    lock.unlock();

    Section popped = thisStack.top();
    popped.end = _clock.now();

    if (popped.tag != tag)
    {
        CORE_THROW("Profiler", "Improper stacking push/pop sequence! " + tag + " != " + popped.tag);
    }
    thisStack.pop();

    if (thisStack.empty())
    {
        _AddSection(std::move(popped));
    }
    else
    {
        thisStack.top().sections.push_back(popped);
    }
}

const std::vector<Section> Profiler::GetSections() const
{
    auto lock = _LockSections();
    return _sections;
}

const std::vector<Section> Profiler::GetSectionsThenClear()
{
    auto lock = _LockSections();
    std::vector<Section> sections = _sections;
    _sections.clear();

    return sections;
}

void Profiler::ClearSections()
{
    auto lock = _LockSections();
    _sections.clear();
}

std::unique_lock<std::mutex> Profiler::_LockSections() const
{
    return std::unique_lock(_sectionMutex);
}

std::unique_lock<std::mutex> Profiler::_LockStacks() const
{
    return std::unique_lock(_stackMutex);
}

void Profiler::_AddSection(Section&& section)
{
    auto lock = _LockSections();
    _sections.emplace_back(std::move(section));
}
#endif
} // namespace Profiling
}// namespace Core