#include "Pipeline/Factory_Temp/FactoryUI.h"

#if DEBUG
#include "Core/Debugging/Profiling/Utils.h"
#endif

#include "Pipeline/Headers/ApplicationManager.h"
#include "Pipeline/Factory_Temp/ArchetypesUI.h"
#include "Pipeline/Factory_Temp/EntitySnapshotUI.h"
#include "Pipeline/Factory_Temp/Factory.h"

namespace Editor {
FactoryUI::FactoryUI(Factory& factory)
: _factory(factory)
{}

void FactoryUI::Initialize()
{
    DEBUG_PROFILE_SCOPE("FactoryUI::Initialize");
    
    _archetypesUI = _factory.GetApplication().RenderManager().GetUIManager().AddWindow<UI::IMGUI::ArchetypesUI>(_factory);
    _entityUI = _factory.GetApplication().RenderManager().GetUIManager().AddWindow<UI::IMGUI::EntitySnapshotUI>(_factory);
}

void FactoryUI::Start()
{
    DEBUG_PROFILE_SCOPE("FactoryUI::Start");
}

void FactoryUI::Update(Core::Second& deltaTime)
{
    DEBUG_PROFILE_SCOPE("FactoryUI::Update");
}

void FactoryUI::End()
{
    DEBUG_PROFILE_SCOPE("FactoryUI::End");
}

void FactoryUI::CleanUp()
{
    DEBUG_PROFILE_SCOPE("FactoryUI::CleanUp");

    _factory.GetApplication().RenderManager().GetUIManager().RemoveWindow(_archetypesUI);
    _factory.GetApplication().RenderManager().GetUIManager().RemoveWindow(_entityUI);

    _archetypesUI = Core::instanceId<Application::UI::IMGUI::Window>();
    _entityUI = Core::instanceId<Application::UI::IMGUI::Window>();
}

void FactoryUI::SelectEntity(Application::EntityId entity)
{
    auto& entitySnapshotUI = EntitySnapshotUI();
    entitySnapshotUI.SetEntity(entity);
}

UI::IMGUI::ArchetypesUI& FactoryUI::ArchetypesUI()
{
    return _factory.GetApplication().RenderManager().GetUIManager().GetWindow<UI::IMGUI::ArchetypesUI>(_archetypesUI);
}

UI::IMGUI::EntitySnapshotUI& FactoryUI::EntitySnapshotUI()
{
    return _factory.GetApplication().RenderManager().GetUIManager().GetWindow<UI::IMGUI::EntitySnapshotUI>(_entityUI);
}
} // namespace Editor