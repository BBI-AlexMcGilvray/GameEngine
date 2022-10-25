#pragma once

#include "Core/Headers/PtrDefs.h"

#include "Pipeline/ECS/DataOriented/EntitySnapshot.h"
#include "Pipeline/UI/IMGUI/Window.h"

#include "Pipeline/Factory_Temp/EntitySnapshotUIVisitor.h"

namespace Editor {
    class Factory;

namespace UI {
// this serves as the base level stuff for factory ui (aka an editor window)
//      -> the 'details' ui will be an instance/part of this that shows what is currently selected
namespace IMGUI {
    class EntitySnapshotUI : public Application::UI::IMGUI::Window
    {
    public:
        EntitySnapshotUI(Factory& factory);

        void Draw() override;

        void SetEntity(Application::EntityId entity);

    private:
        UIVisitor _uiVisitor;
        Factory& _factory;
        
        Application::EntityId _entity;
    };
} // namespace IMGUI
} // namespace UI
} // namespace Editor