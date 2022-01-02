#include "Product/Headers/MyProduct.h"

// testing
#include "Pipeline/Headers/ApplicationManager.h"
#include "Pipeline/StateSystem/Headers/StateManager.h"

#include "Pipeline/Geometric/Headers/CameraNode.h"
#include "Pipeline/Geometric/Headers/ContentBase.h"
#include "Pipeline/Geometric/Headers/Node.h"

#include "Pipeline/ECSSystems/AnimationComponents.h"
#include "Pipeline/ECSSystems/CameraComponents.h"
#include "Pipeline/ECSSystems/GeneralComponents.h"
#include "Pipeline/ECSSystems/RenderingComponents.h"
#include "Pipeline/ECSSystems/TransformComponents.h"

#include "Pipeline/Rendering/Material_NEW.h"
#include "Pipeline/Rendering/Mesh_NEW.h"

#include "Pipeline/Rendering/3D/Headers/ModelBase.h"
#include "Pipeline/Rendering/3D/Headers/AnimatedModel.h"

#include "Pipeline/Input/Headers/InputController.h"
#include "Pipeline/Input/Headers/InputManager.h"

#include "Product/Supplies/Assets.h"

#include "Core/Math/Headers/UtilityFunctions.h"
#include "Core/Math/Headers/MatrixFunctions.h"
// \testing

namespace Product
{
    void MyProduct::initialize()
    {
        Application::StateManager& stateManager = Application::ApplicationManager::AppStateManager();
        Application::State& currentState = stateManager.GetActiveState();

        _luaManager.initialize();

        // testing
        auto& animationManager = Application::ApplicationManager::AppAnimationManager();
        auto& assetManager = Application::ApplicationManager::AppAssetManager();
        auto& ecs = Application::ApplicationManager::AppECS();
        auto& shaderManager = Application::ApplicationManager::AppShaderManager();

        // this will be data driven from the future
        // create camera
        Transform cameraTransform;
        Application::CameraComponent camera(1280.0f / 1080.0f, Core::Math::Float3(0.0f, 0.0f, 0.0f));
        auto cameraComponents = std::make_tuple<Application::CameraComponent, Application::WorldTransformComponent, Application::PositionComponent, Application::RotationComponent>(std::move(camera), cameraTransform, Core::Math::Float3(0.0f, 0.0f, 20.0f), Core::Math::FQuaternion(Core::Math::II()));
        _camera = ecs.CreateEntity(cameraComponents);

        // create camera controller
        _cameraController = CameraController(ecs, _camera.GetEntityId());
        Application::Input::InputManager& inputManager = Application::ApplicationManager::AppInputManager();
        inputManager.setInputController<Application::Input::DefaultInputController>();
        inputManager->addReceiver(&_cameraController);

        // create MI
        // auto material = CreateMaterial(assetManager.getAssetData(Data::Ast.mat.MI_0), shaderManager);
        // auto mesh = CreateMesh(assetManager.getAssetData(Data::Ast.smsh.MI_0));
        // Transform transform = Transform();

        // auto components = std::make_tuple<Application::WorldTransformComponent, Application::PositionComponent, Application::RotationComponent, Application::MaterialComponent, Application::MeshComponent>(transform, Core::Math::Float3(0.0f, 0.0f, -600.0f), Core::Math::FQuaternion(Core::Math::II()), material, mesh);
        // _mi = ecs.CreateEntity(components);
        Application::Rendering::InitialStaticModelState initialMIState(Data::Ast.smdl.MI_0, Transform());
        _mi = Application::Rendering::CreateModel(ecs, assetManager, shaderManager, initialMIState);

        // create Woman
        /*
        NOTE: We are never 'skinning' the mesh (assigning the bone indices)
            - maybe we can do this when we create the mesh by providing the skeleton data?
            - maybe we need to do this after, in which case we should provide a skeleton component (that includes an array of strings (hashes?) to match entity ids and allow us to get indices)
                - the array of strings should probably exist anyways so we can get the bone (entityId) based on the name (hashed name?)
        */
        Application::Rendering::InitialAnimatedModelState initialWomanState(Data::Ast.amdl.Woman_0, Transform());
        _woman = Application::Rendering::CreateModel(ecs, assetManager, animationManager, shaderManager, initialWomanState);
        // ecs.GetComponentFor<Application::RotationComponent>(_woman).rotation = FQuaternion(0.0f, 0.707f, 0.0f, 0.707f) * FQuaternion(-0.707f, 0.0f, 0.0f, 0.707f);
        // \testing
    }

    void MyProduct::start()
    {
        _luaManager.start();

        auto& animationComponent = Application::ApplicationManager::AppECS().GetComponentFor<Application::AnimatorComponent>(_woman);
        Application::ApplicationManager::AppAnimationManager().GetAnimator(animationComponent.animatorId).PlayAnimation(Data::Ast.sanim.Woman_0_Armature_Idle);
    }

    void MyProduct::update(Core::Second dt)
    {
        _luaManager.update(dt);

        // testing local transforms by rotating arm
        // Application::SkeletonComponent& skeleton = Application::ApplicationManager::AppECS().GetComponentFor<Application::SkeletonComponent>(_woman);
        // Application::EntityId skeletonShoulder = skeleton.GetBone("LeftShoulder");

        // Application::RotationComponent& armRotation = Application::ApplicationManager::AppECS().GetComponentFor<Application::RotationComponent>(skeletonShoulder);
        // FQuaternion currentRotation = armRotation.rotation;
        // FQuaternion newRot = Core::Math::LerpQuat(currentRotation, FQuaternion(0.0f, 0.1f, 0.0f, 0.9f) * currentRotation, Duration(dt));
        // armRotation.rotation = newRot;
        // \testing

        // testing
        Application::RotationComponent& entityRotationComponent = Application::ApplicationManager::AppECS().GetComponentFor<Application::RotationComponent>(_mi);
        
        FQuaternion entityRotation = entityRotationComponent.rotation;
        FQuaternion newEntityRotation = Core::Math::LerpQuat(entityRotation, FQuaternion(0.0f, 0.1f, 0.0f, 0.9f) * entityRotation, Duration(dt));
        entityRotationComponent.rotation = newEntityRotation;
        // \testing
    }

    void MyProduct::end()
    {
        _luaManager.end();
    }

    void MyProduct::cleanUp()
    {
        _luaManager.cleanUp();
    }
}