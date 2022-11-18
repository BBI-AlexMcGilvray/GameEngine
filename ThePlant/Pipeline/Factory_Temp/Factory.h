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
    };
} // namespace Editor