#pragma once

#include "Pipeline/UI/IMGUI/Manager.h"

#include "Pipeline/UI/IMGUI/Windows/Examples.h"
#include "Pipeline/UI/IMGUI/Windows/MemoryTracker.h"
#include "Pipeline/UI/IMGUI/Windows/Profiler.h"
#include "Pipeline/UI/IMGUI/Windows/SystemTracker.h"

namespace Application {
namespace UI {
namespace IMGUI {
void RegisterDefaultWindows(Manager& manager)
{
#if DEBUG
    manager.AddWindow<Examples>();
    manager.AddWindow<MemoryTracker>();
    manager.AddWindow<Profiler>();
    manager.AddWindow<SystemTracker>();
#endif
}
}// namespace IMGUI
}// namespace UI
}// namespace Application