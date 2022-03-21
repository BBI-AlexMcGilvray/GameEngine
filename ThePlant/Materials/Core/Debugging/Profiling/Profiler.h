#pragma once

#include <string>
#include <vector>
#include <stack>
#include <unordered_map>

#include "Core/Debugging/Headers/Macros.h"
#include "Core/Debugging/Headers/Declarations.h"
#include "Core/Headers/TimeDefs.h"
#include "Core/Threading/Thread.h"

namespace Core {
namespace Profiling
{
#if DEBUG
struct Section
{
    std::string tag;
    TimePoint start;
    TimePoint end;
    std::vector<Section> sections;

    Section(const std::string& tag, SteadyClock& clock)
    : tag(tag)
    , start(clock.now())
    {
        sections.reserve(4); // try to avoid moving the vector multiple times
    }

    Section(const Section&) = default;
    Section(Section&&) = default;

    Section& operator=(const Section&) = default;
    Section& operator=(Section&&) = default;
};

struct Profiler
{
    Profiler() = default;

    void Push(const std::string& tag);
    void Pop(const std::string& tag);

    const std::vector<Section> GetSections() const;
    const std::vector<Section> GetSectionsThenClear();
    void ClearSections();
    
private:
    SteadyClock _clock;

    mutable std::mutex _sectionMutex;
    std::vector<Section> _sections;

    mutable std::mutex _stackMutex;
    std::unordered_map<Threading::ThreadId, std::stack<Section>> _threadStacks;

    std::unique_lock<std::mutex> _LockSections() const;
    std::unique_lock<std::mutex> _LockStacks() const;

    void _AddSection(Section&& section);
};
#endif
} // namespace Profiling
}// namespace Core