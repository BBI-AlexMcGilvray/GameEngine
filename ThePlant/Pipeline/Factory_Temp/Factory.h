#pragma once

#include "Core/Headers/PtrDefs.h"
#include "Core/Headers/TimeDefs.h"

#include "Pipeline/Factory_Temp/FactoryUI.h"

namespace Application
{
    struct ApplicationManager;
} // namespace Application

/*
Notes:
- We should have a registration process for 'editor systems'
    - only these systems are run in 'edit' mode (ex: rendering)
- Factory should have a state that it holds/loads/save
    - there can be a default state when working on smaller assets (meshes, entity prefabs)
    - play mode kicks off the application in that state
        - when the above happens, we should copy the ECS entities to the newly activated ECS system
            - we should be able to specify a 'copy all' vs 'copy entities'
                - the latter is to facilitate copying entities between states in levels
                - the former is for the same, but also to copy things from editor->play mode
*/

namespace Editor {
    class Factory
    {
        public:
            Factory(Application::ApplicationManager& application);

            void Initialize();
            void Start();
            void Update(Core::Second& deltaTime);
            void End();
            void CleanUp();

            Application::ApplicationManager& GetApplication();
            FactoryUI& GetFactoryUI();

            // should this be here? maybe
            void SelectEntity(Application::EntityId entity);

        private:
            Application::ApplicationManager& _application;
            FactoryUI _factoryUI;

            // std::unique_ptr<Application::State> _editingState;
    };
} // namespace Editor