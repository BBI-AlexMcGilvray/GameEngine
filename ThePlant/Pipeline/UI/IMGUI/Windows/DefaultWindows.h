#pragma once

#include "Core/Debugging/Headers/Declarations.h"

#include "Pipeline/UI/IMGUI/Manager.h"

#include "Pipeline/UI/IMGUI/Windows/Examples.h"
#include "Pipeline/UI/IMGUI/Windows/Profiler.h"

namespace Application {
namespace UI {
namespace IMGUI {
void RegisterDefaultWindows(Manager& manager)
{
#if DEBUG
    manager.AddWindow<Examples>();
    manager.AddWindow<Profiler>();
#endif
}
}// namespace IMGUI
}// namespace UI
}// namespace Application