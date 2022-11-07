#include "Pipeline/Utils/RegisterUtils.h"

#include "Pipeline/Factory_Temp/FactoryUI.h"
#include "Pipeline/Factory_Temp/EntitySnapshotUI.h"

#include "Pipeline/ECSSystems/AnimationComponents.h"
#include "Pipeline/ECSSystems/CameraComponents.h"
#include "Pipeline/ECSSystems/ColliderComponents.h"
#include "Pipeline/ECSSystems/GeneralComponents.h"
#include "Pipeline/ECSSystems/LifetimeComponent.h"
#include "Pipeline/ECSSystems/RenderingComponents.h"
#include "Pipeline/ECSSystems/TransformComponents.h"
#include "Pipeline/Physics/PhysicsComponents.h"

/*
NOTE: We could make a macro to register to all required factories, but this allows for customizing UI/loading individually (even though everything is default at the moment)
*/

namespace Application {
void RegisterComponentRefUI(Editor::UI::IMGUI::ComponentRefUIFactory& componentRefUI)
{
    // animation components
    componentRefUI.DefaultRegister<AnimationComponent>();
    componentRefUI.DefaultRegister<AnimatorComponent>();

    // camera components
    componentRefUI.DefaultRegister<CameraComponent>();
    componentRefUI.DefaultRegister<CameraWeightingComponent>();

    // collision components
    componentRefUI.DefaultRegister<ColliderComponent>();

    // general components
    componentRefUI.DefaultRegister<ParentComponent>();
    componentRefUI.DefaultRegister<ChildComponent>();

    // lifetime components
    componentRefUI.DefaultRegister<LifetimeComponent>();

    // physics components
    componentRefUI.DefaultRegister<RigidBodyComponent>();
    componentRefUI.DefaultRegister<VelocityComponent>();
    componentRefUI.DefaultRegister<PhysicsComponent>();

    // rendering components
    componentRefUI.DefaultRegister<ColorComponent>();
    componentRefUI.DefaultRegister<MaterialComponent>();
    componentRefUI.DefaultRegister<MeshComponent>();
    componentRefUI.DefaultRegister<SkinnedMeshComponent>();
    componentRefUI.DefaultRegister<BoneComponent>();
    componentRefUI.DefaultRegister<SkeletonComponent>();

    // transform components
    componentRefUI.DefaultRegister<PositionComponent>();
    componentRefUI.DefaultRegister<RotationComponent>();
    componentRefUI.DefaultRegister<ScaleComponent>();
    componentRefUI.DefaultRegister<WorldTransformComponent>();
}

void RegisterEntityFactory(Application::EntityFactory& entityFactory)
{
    // animation components
    entityFactory.DefaultRegister<AnimationComponent>();
    entityFactory.DefaultRegister<AnimatorComponent>();

    // camera components
    entityFactory.DefaultRegister<CameraComponent>();
    entityFactory.DefaultRegister<CameraWeightingComponent>();

    // collision components
    entityFactory.DefaultRegister<ColliderComponent>();

    // general components
    entityFactory.DefaultRegister<ParentComponent>();
    entityFactory.DefaultRegister<ChildComponent>();

    // lifetime components
    entityFactory.DefaultRegister<LifetimeComponent>();

    // physics components
    entityFactory.DefaultRegister<RigidBodyComponent>();
    entityFactory.DefaultRegister<VelocityComponent>();
    entityFactory.DefaultRegister<PhysicsComponent>();

    // rendering components
    entityFactory.DefaultRegister<ColorComponent>();
    entityFactory.DefaultRegister<MaterialComponent>();
    entityFactory.DefaultRegister<MeshComponent>();
    entityFactory.DefaultRegister<SkinnedMeshComponent>();
    entityFactory.DefaultRegister<BoneComponent>();
    entityFactory.DefaultRegister<SkeletonComponent>();

    // transform components
    entityFactory.DefaultRegister<PositionComponent>();
    entityFactory.DefaultRegister<RotationComponent>();
    entityFactory.DefaultRegister<ScaleComponent>();
    entityFactory.DefaultRegister<WorldTransformComponent>();
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