#include "Pipeline/Factory_Temp/FactoryUI.h"

#if DEBUG
#include "Core/Debugging/Profiling/Utils.h"
#endif

#include "Pipeline/Headers/ApplicationManager.h"
#include "Pipeline/Factory_Temp/EntitySnapshotUI.h"
#include "Pipeline/Factory_Temp/Factory.h"

namespace Editor {
FactoryUI::FactoryUI(Factory& factory)
: _factory(factory)
{}

void FactoryUI::Initialize()
{
    DEBUG_PROFILE_SCOPE("FactoryUI::CleanUp");
    
    _entityUI = _factory.GetApplication().RenderManager().GetUIManager().AddWindow<UI::IMGUI::EntitySnapshotUI>(_factory);
}

void FactoryUI::Start()
{
    DEBUG_PROFILE_SCOPE("FactoryUI::CleanUp");
}

void FactoryUI::Update(Core::Second& deltaTime)
{
    DEBUG_PROFILE_SCOPE("FactoryUI::CleanUp");
}

void FactoryUI::End()
{
    DEBUG_PROFILE_SCOPE("FactoryUI::CleanUp");
}

void FactoryUI::CleanUp()
{
    DEBUG_PROFILE_SCOPE("FactoryUI::CleanUp");

    _factory.GetApplication().RenderManager().GetUIManager().RemoveWindow(_entityUI);
    _entityUI = Core::instanceId<Application::UI::IMGUI::Window>();
}

void FactoryUI::SelectEntity(Application::EntityId entity)
{
    auto& entitySnapshotUI = EntitySnapshotUI();
    entitySnapshotUI.SetEntity(entity);
}

UI::IMGUI::EntitySnapshotUI& FactoryUI::EntitySnapshotUI()
{
    return _factory.GetApplication().RenderManager().GetUIManager().GetWindow<UI::IMGUI::EntitySnapshotUI>(_entityUI);
}
} // namespace Editor