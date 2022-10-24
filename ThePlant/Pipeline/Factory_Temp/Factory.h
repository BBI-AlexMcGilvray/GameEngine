#pragma once

#include "Core/Headers/PtrDefs.h"
#include "Core/Headers/TimeDefs.h"

#include "Pipeline/Factory_Temp/FactoryUI.h"

namespace Application
{
    struct ApplicationManager;
} // namespace Application

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

            // should this be here? maybe
            void SelectEntity(Application::EntityId entity);

        private:
            Application::ApplicationManager& _application;
            FactoryUI _factoryUI;
    };
} // namespace Editor