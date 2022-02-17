#include "Pipeline/Debugging/Profiling/Profiler.h"

namespace Application {
namespace Profiling
{
#if DEBUG
void Profiler::Push(const std::string& tag)
{
    _stack.push(Section(tag, _clock));
}

void Profiler::Pop(const std::string& tag)
{
    Section popped = _stack.top();
    popped.end = _clock.now();
    _stack.pop();

    if (_stack.empty())
    {
        _sections.push_back(popped);
    }
    else
    {
        _stack.top().sections.push_back(popped);
    }
}

const std::vector<Section> Profiler::GetSections() const
{
    return _sections;
}

void Profiler::Clear()
{
    VERIFY(_stack.empty());
    _sections.clear();
}
#endif
} // namespace Profiling
}// namespace Application