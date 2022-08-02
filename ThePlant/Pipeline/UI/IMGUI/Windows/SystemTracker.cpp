#include "Pipeline/UI/IMGUI/Windows/SystemTracker.h"

#include "Core/Headers/Service.h"

#include "Pipeline/Headers/ServiceManager.h"
#include "Pipeline/Headers/ApplicationManager.h"
#include "Pipeline/ECS/DataOriented/ECS.h"

namespace Application {
namespace UI {
namespace IMGUI {
void SystemTracker::Draw()
{
    WITH_DEBUG_SERVICE(ApplicationWrapper)
    (
        auto& ecs = service->application->StateManager().GetActiveState().ECS();
        for (auto& system : ecs.GetCurrentSystems())
        {
            ImGui::Checkbox(system->GetName().c_str(), &(system->active));
        }
    )
}
}// namespace IMGUI
}// namespace UI
}// namespace Application