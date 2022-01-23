#include "Product/Testing/TestingUtils.h"

#include "Pipeline/Headers/ApplicationManager.h"

#include "Pipeline/ECS/DataOriented/EntityCreator.h"

#include "Pipeline/ECSSystems/AnimationComponents.h"
#include "Pipeline/ECSSystems/CameraComponents.h"
#include "Pipeline/ECSSystems/ColliderComponents.h"
#include "Pipeline/ECSSystems/GeneralComponents.h"
#include "Pipeline/ECSSystems/RenderingComponents.h"
#include "Pipeline/ECSSystems/TransformComponents.h"

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
    Application::Entity SpawnStaticModel()
    {
        auto& assetManager = Application::ApplicationManager::AppAssetManager();
        auto& ecs = Application::ApplicationManager::AppECS();
        auto& shaderManager = Application::ApplicationManager::AppShaderManager();

        Application::Rendering::InitialStaticModelState initialMIState(Data::Ast.smdl.MI_0, Core::Geometric::Transform());
        return Application::Rendering::CreateModel(ecs, assetManager, shaderManager, initialMIState);
    }

    Application::Entity SpawnAnimatedModel()
    {
        auto& animationManager = Application::ApplicationManager::AppAnimationManager();
        auto& assetManager = Application::ApplicationManager::AppAssetManager();
        auto& ecs = Application::ApplicationManager::AppECS();
        auto& shaderManager = Application::ApplicationManager::AppShaderManager();

        Application::Rendering::InitialAnimatedModelState initialWomanState(Data::Ast.amdl.Monk_1, Core::Geometric::Transform());
        return Application::Rendering::CreateModel(ecs, assetManager, animationManager, shaderManager, initialWomanState);
    }

    Application::Entity SpawnCollider(const Core::Geometric::Shape3D& shape, const Core::Math::Float3& position, const Core::Math::FQuaternion& rotation, const Core::Math::Float3& scale)
    {
        auto& ecs = Application::ApplicationManager::AppECS();

        Application::EntityCreator creator;
        creator.AddComponent<Application::PositionComponent>(position);
        creator.AddComponent<Application::RotationComponent>(rotation);
        creator.AddComponent<Application::ScaleComponent>(scale);
        creator.AddComponent<Application::WorldTransformComponent>();
        creator.AddComponent<Application::ColliderComponent>(shape, false);

        return ecs.CreateEntity(creator);
    }

    Application::Entity SpawnTrigger(const Core::Geometric::Shape3D& shape, const Core::Math::Float3& position, const Core::Math::FQuaternion& rotation, const Core::Math::Float3& scale)
    {
        auto& ecs = Application::ApplicationManager::AppECS();

        Application::EntityCreator creator;
        creator.AddComponent<Application::PositionComponent>(position);
        creator.AddComponent<Application::RotationComponent>(rotation);
        creator.AddComponent<Application::ScaleComponent>(scale);
        creator.AddComponent<Application::WorldTransformComponent>();
        creator.AddComponent<Application::ColliderComponent>(shape, true);

        return ecs.CreateEntity(creator);
    }
} // namespace Testing
} // namespace Product