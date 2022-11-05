#include "Pipeline/Factory_Temp/FactoryUtils.h"

#include "Pipeline/ECSSystems/TransformComponents.h"
#include "Pipeline/ECSSystems/ColliderComponents.h"
#include "Pipeline/Physics/PhysicsComponents.h"

namespace Editor {
void RegisterComponents(ComponentRefUI& componentRefUI)
{
    // transform components
    componentRefUI.Register<Application::PositionComponent>();
    componentRefUI.Register<Application::RotationComponent>();
    componentRefUI.Register<Application::ScaleComponent>();
    componentRefUI.Register<Application::WorldTransformComponent>();

    // collision components
    componentRefUI.Register<Application::ColliderComponent>();

    // physics components
    componentRefUI.Register<Application::RigidBodyComponent>();
}
} // namespace Editor