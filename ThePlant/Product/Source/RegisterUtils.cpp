#include "Product/Headers/RegisterUtils.h"

#include "Pipeline/Factory_Temp/FactoryUI.h"
#include "Pipeline/Factory_Temp/EntitySnapshotUI.h"

#include "Product/Testing/TestSystem.h"

namespace Product {
void RegisterComponentRefUI(Editor::UI::IMGUI::ComponentRefUIFactory& componentRefUI)
{
    componentRefUI.DefaultRegister<Testing::CollisionCountComponent>();
    componentRefUI.DefaultRegister<Testing::DestroyOnCollisionComponent>();
}

void RegisterEntityFactory(Application::EntityFactory& entityFactory)
{
    entityFactory.DefaultRegister<Testing::CollisionCountComponent>();
    entityFactory.DefaultRegister<Testing::DestroyOnCollisionComponent>();
}

void RegisterComponents(Application::ApplicationManager& application)
{
    WITH_DEBUG_SERVICE(Editor::Factory)
    (
        RegisterComponentRefUI(service->GetFactoryUI().EntitySnapshotUI().GetComponentRefUIFactory());
    )
    RegisterEntityFactory(application.EntityFactory());
}
} // namespace Editor