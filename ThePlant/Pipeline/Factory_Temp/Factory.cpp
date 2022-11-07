#include "Pipeline/Factory_Temp/Factory.h"

#if DEBUG
#include "Core/Debugging/Profiling/Utils.h"
#endif

#include "Pipeline/Headers/ApplicationManager.h"

namespace Editor {
Factory::Factory(Application::ApplicationManager& application)
: _application(application)
, _factoryUI(*this)
{}

void Factory::Initialize()
{
    DEBUG_PROFILE_SCOPE("Factory::Initialize");
    _factoryUI.Initialize();
}

void Factory::Start()
{
    DEBUG_PROFILE_SCOPE("Factory::Start");
    _factoryUI.Start();
}

void Factory::Update(Core::Second& deltaTime)
{
    DEBUG_PROFILE_SCOPE("Factory::Update");
    _factoryUI.Update(deltaTime);
}

void Factory::End()
{
    DEBUG_PROFILE_SCOPE("Factory::End");
    _factoryUI.End();
}

void Factory::CleanUp()
{
    DEBUG_PROFILE_SCOPE("Factory::CleanUp");
    _factoryUI.CleanUp();
}

Application::ApplicationManager& Factory::GetApplication()
{
    return _application;
}

FactoryUI& Factory::GetFactoryUI()
{
    return _factoryUI;
}

void Factory::SelectEntity(Application::EntityId entity)
{
    _factoryUI.SelectEntity(entity);
}
} // namespace Editor