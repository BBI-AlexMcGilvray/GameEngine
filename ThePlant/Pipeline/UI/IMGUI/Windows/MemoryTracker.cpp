#include "Pipeline/UI/IMGUI/Windows/MemoryTracker.h"

#include <format>

#include "Core/Headers/Service.h"

namespace Application {
namespace UI {
namespace IMGUI {

void MemoryTracker::Draw()
{
    if (ImGui::Button("Update Memory"))
    {
        WITH_DEBUG_SERVICE(Core::Memory::MemoryTracker)
        (
            _currentMemoryInfo = service->Info();
        )
    }
    
    ImGui::Text(_currentMemoryInfo.c_str());
}

}// namespace IMGUI
}// namespace UI
}// namespace Application