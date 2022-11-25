#include "Pipeline/Factory_Temp/ArchetypesUI.h"

#include "Core/Headers/CoreDefs.h"

#include "Pipeline/Dependencies/IMGUI/imgui.h"
#include "Pipeline/ECS/DataOriented/ECS.h"
#include "Pipeline/Headers/ApplicationManager.h"
#include "Pipeline/Factory_Temp/Factory.h"

namespace Editor::UI {
// this serves as the base level stuff for factory ui (aka an editor window)
//      -> the 'details' ui will be an instance/part of this that shows what is currently selected
namespace IMGUI {
ArchetypesUI::ArchetypesUI(Factory& factory)
: Application::UI::IMGUI::Window("ArchetypesUI")
, _factory(factory)
{}

// should this be done through a system?
// the hierarchy one should be, we should have a system that builds the hierarchy every frame
//      - should that system then be re-used by the transform system? possible optimization for later
void ArchetypesUI::Draw()
{
    Application::ECS& ecs = _factory.GetApplication().StateManager().GetActiveState().ECS();

    // std::hash<Application::EntityId> hasher;
    // ImGui::Text(std::to_string(hasher(_entity)).c_str());

    // Application::EntitySnapshot snapshot = _factory.GetApplication().StateManager().GetActiveState().ECS().GetTemporaryEntitySnapshot(_entity);
    // _uiFactory.Visit(snapshot);
}

// ComponentRefUIFactory& EntitySnapshotUI::GetComponentRefUIFactory()
// {
//     return _uiFactory;
// }
}// namespace IMGUI
} // namespace Editor::UI