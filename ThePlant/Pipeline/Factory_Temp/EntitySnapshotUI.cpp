#include "Pipeline/Factory_Temp/EntitySnapshotUI.h"

#include "Core/Headers/CoreDefs.h"

#include "Pipeline/Dependencies/IMGUI/imgui.h"
#include "Pipeline/Headers/ApplicationManager.h"
#include "Pipeline/Factory_Temp/Factory.h"

namespace Editor::UI {
// this serves as the base level stuff for factory ui (aka an editor window)
//      -> the 'details' ui will be an instance/part of this that shows what is currently selected
namespace IMGUI {
EntitySnapshotUI::EntitySnapshotUI(Factory& factory)
: Application::UI::IMGUI::Window("EntitySnapshotUI")
, _factory(factory)
{}

void EntitySnapshotUI::Draw()
{
    if (!_entity.IsValid())
    {
        ImGui::Text("No entity selected");
        return;
    }

    std::hash<Application::EntityId> hasher;
    ImGui::Text(std::to_string(hasher(_entity)).c_str());

    auto& application = _factory.GetApplication();
    auto& stateManager = application.StateManager();
    auto& activeState = stateManager.GetActiveState();
    auto& ecs = activeState.ECS();
    Application::EntitySnapshot snapshot = ecs.GetTemporaryEntitySnapshot(_entity);
    _uiVisitor.Visit(snapshot);
}

void EntitySnapshotUI::SetEntity(Application::EntityId entity)
{
    _entity = entity;
}
}// namespace IMGUI
} // namespace Editor::UI