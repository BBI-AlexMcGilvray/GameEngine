#include "Product/Testing/TestingUtils.h"

#include "Pipeline/Headers/ApplicationManager.h"

#include "Pipeline/ECS/DataOriented/EntityCreator.h"

#include "Pipeline/ECSSystems/AnimationComponents.h"
#include "Pipeline/ECSSystems/CameraComponents.h"
#include "Pipeline/ECSSystems/ColliderComponents.h"
#include "Pipeline/ECSSystems/GeneralComponents.h"
#include "Pipeline/ECSSystems/RenderingComponents.h"
#include "Pipeline/ECSSystems/TransformComponents.h"
#include "Pipeline/Physics/PhysicsComponents.h"

#include "Pipeline/Rendering/Material.h"
#include "Pipeline/Rendering/Mesh.h"

#include "Pipeline/Rendering/3D/Headers/ModelBase.h"
#include "Pipeline/Rendering/3D/Headers/AnimatedModel.h"

#include "Pipeline/Input/Headers/InputController.h"
#include "Pipeline/Input/Headers/InputManager.h"

#include "Product/Supplies/Assets.h"

namespace Product
{
namespace Testing
{
    Application::Entity SpawnStaticModel(Application::State& state)
    {
        auto& assetManager = state.AssetManager();
        auto& ecs = state.ECS();
        auto& shaderManager = state.ShaderManager();

        Application::Rendering::InitialStaticModelState initialMIState(Data::Ast.smdl.MI_0, Core::Geometric::Transform());
        return Application::Rendering::CreateModel(ecs, assetManager, shaderManager, initialMIState);
    }

    Application::Entity SpawnAnimatedModel(Application::State& state)
    {
        auto& animationManager = state.AnimationManager();
        auto& assetManager = state.AssetManager();
        auto& ecs = state.ECS();
        auto& shaderManager = state.ShaderManager();

        Application::Rendering::InitialAnimatedModelState initialWomanState(Data::Ast.amdl.Monk_1, Core::Geometric::Transform());
        return Application::Rendering::CreateModel(ecs, assetManager, animationManager, shaderManager, initialWomanState);
    }

    Application::Entity SpawnCollider(Application::State& state, const Core::Math::Float3& velocity, const Core::Geometric::Shape3D& shape, const Core::Math::Float3& position, const Core::Math::FQuaternion& rotation, const Core::Math::Float3& scale)
    {
        auto& ecs = state.ECS();

        Application::EntityCreator creator;
        creator.AddComponent<Application::PositionComponent>(position);
        creator.AddComponent<Application::RotationComponent>(rotation);
        creator.AddComponent<Application::ScaleComponent>(scale);
        creator.AddComponent<Application::WorldTransformComponent>();
        creator.AddComponent<Application::ColliderComponent>(shape, false, false);
        creator.AddComponent<Application::VelocityComponent>(velocity);
        creator.AddComponent<Application::RigidBodyComponent>(1.0f, 0.0f, 0.0f, 1.0f);
        creator.AddComponent<Application::PhysicsComponent>(1.0f, 100.0f);

        return ecs.CreateEntity(creator);
    }

    Application::Entity SpawnStaticCollider(Application::State& state, const Core::Geometric::Shape3D& shape, const Core::Math::Float3& position, const Core::Math::FQuaternion& rotation, const Core::Math::Float3& scale)
    {
        auto& ecs = state.ECS();

        Application::EntityCreator creator;
        creator.AddComponent<Application::PositionComponent>(position);
        creator.AddComponent<Application::RotationComponent>(rotation);
        creator.AddComponent<Application::ScaleComponent>(scale);
        creator.AddComponent<Application::WorldTransformComponent>();
        creator.AddComponent<Application::ColliderComponent>(shape, false, true);
        creator.AddComponent<Application::RigidBodyComponent>(1.0f, 0.0f, 0.0f, 1.0f);

        return ecs.CreateEntity(creator);
    }

    Application::Entity SpawnTrigger(Application::State& state, const Core::Math::Float3& velocity, const Core::Geometric::Shape3D& shape, const Core::Math::Float3& position, const Core::Math::FQuaternion& rotation, const Core::Math::Float3& scale)
    {
        auto& ecs = state.ECS();

        Application::EntityCreator creator;
        creator.AddComponent<Application::PositionComponent>(position);
        creator.AddComponent<Application::RotationComponent>(rotation);
        creator.AddComponent<Application::ScaleComponent>(scale);
        creator.AddComponent<Application::WorldTransformComponent>();
        creator.AddComponent<Application::ColliderComponent>(shape, true, false);
        creator.AddComponent<Application::VelocityComponent>(velocity);
        return ecs.CreateEntity(creator);
    }

    Application::Entity SpawnStaticTrigger(Application::State& state, const Core::Geometric::Shape3D& shape, const Core::Math::Float3& position, const Core::Math::FQuaternion& rotation, const Core::Math::Float3& scale)
    {
        auto& ecs = state.ECS();

        Application::EntityCreator creator;
        creator.AddComponent<Application::PositionComponent>(position);
        creator.AddComponent<Application::RotationComponent>(rotation);
        creator.AddComponent<Application::ScaleComponent>(scale);
        creator.AddComponent<Application::WorldTransformComponent>();
        creator.AddComponent<Application::ColliderComponent>(shape, true, true);

        return ecs.CreateEntity(creator);
    }
} // namespace Testing
} // namespace Product