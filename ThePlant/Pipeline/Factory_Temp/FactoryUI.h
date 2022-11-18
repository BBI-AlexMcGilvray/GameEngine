#pragma once

#include "Core/Headers/PtrDefs.h"
#include "Core/Headers/TimeDefs.h"

#include "Pipeline/ECS/DataOriented/IDs.h"
#include "Pipeline/UI/IMGUI/Window.h"

namespace Editor {
    class Factory;
    namespace UI
    {
        namespace IMGUI
        {
            class ArchetypesUI;
            class EntitySnapshotUI;
        }
    }

    class FactoryUI
    {
        public:
            FactoryUI(Factory& factory);

            void Initialize();
            void Start();
            void Update(Core::Second& deltaTime);
            void End();
            void CleanUp();

            // should this be here? maybe
            void SelectEntity(Application::EntityId entity);

            UI::IMGUI::ArchetypesUI& ArchetypesUI();
            UI::IMGUI::EntitySnapshotUI& EntitySnapshotUI();

        private:
            Factory& _factory;
            Core::instanceId<Application::UI::IMGUI::Window> _entityUI; // in the future, this should probably be a general UI holder that the Factory knows instead of each UI piece
            Core::instanceId<Application::UI::IMGUI::Window> _archetypesUI;
    };
} // namespace Editor