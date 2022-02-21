#pragma once

#include <string>
#include <vector>
#include <stack>

#include "Core/Debugging/Headers/Macros.h"
#include "Core/Debugging/Headers/Declarations.h"
#include "Core/Headers/TimeDefs.h"

namespace Application {
namespace Profiling
{
#if DEBUG
struct Section
{
    std::string tag;
    Core::TimePoint start;
    Core::TimePoint end;
    std::vector<Section> sections;

    Section(const std::string& tag, Core::SteadyClock& clock)
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
    void Clear();
    
private:
    Core::SteadyClock _clock;
    std::vector<Section> _sections;

    std::stack<Section> _stack;
};
#endif
} // namespace Profiling
}// namespace Application