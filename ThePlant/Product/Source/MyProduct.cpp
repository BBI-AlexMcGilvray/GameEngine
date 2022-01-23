#include "Product/Headers/MyProduct.h"

#include "Core/Math/Headers/UtilityFunctions.h"
#include "Core/Math/Headers/MatrixFunctions.h"

#include "Pipeline/Headers/ApplicationManager.h"

#include "Pipeline/ECSSystems/AnimationComponents.h"
#include "Pipeline/ECSSystems/CameraComponents.h"
#include "Pipeline/ECSSystems/GeneralComponents.h"
#include "Pipeline/ECSSystems/RenderingComponents.h"
#include "Pipeline/ECSSystems/TransformComponents.h"

// testing
#include "Product/Testing/TestingUtils.h"
#include "Product/Supplies/Assets.h"
// \testing

namespace Product
{
    void MyProduct::initialize()
    {
        _luaManager.initialize();

        // this will be data driven from the future
        // create camera
        Core::Geometric::Transform cameraTransform;
        Application::CameraComponent camera(1280.0f / 1080.0f, Core::Math::Float3(0.0f, 0.0f, 0.0f));
        auto cameraComponents = std::make_tuple<Application::CameraComponent, Application::WorldTransformComponent, Application::PositionComponent, Application::RotationComponent>(std::move(camera), cameraTransform, Core::Math::Float3(0.0f, 0.0f, 20.0f), Core::Math::FQuaternion(Core::Math::II()));
        _camera = Application::ApplicationManager::AppECS().CreateEntity(cameraComponents);

        // create camera controller
        _cameraController = CameraController(Application::ApplicationManager::AppECS(), _camera.GetEntityId());
        Application::Input::InputManager& inputManager = Application::ApplicationManager::AppInputManager();
        inputManager.setInputController<Application::Input::DefaultInputController>();
        inputManager->addReceiver(&_cameraController);

        // testing
        _static = Testing::SpawnStaticModel();
        _animated = Testing::SpawnAnimatedModel();
        // \testing
    }

    void MyProduct::start()
    {
        _luaManager.start();

        // auto& animationComponent = Application::ApplicationManager::AppECS().GetComponentFor<Application::AnimatorComponent>(_woman);
        // Application::ApplicationManager::AppAnimationManager().GetAnimator(animationComponent.animatorId).PlayAnimation(Data::Ast.sanim.Monk_1_CharacterArmature_Idle);
    }

    // testing
    bool played = false;
    int frames = 0;
    // \testing
    void MyProduct::update(Core::Second dt)
    {
        _luaManager.update(dt);

        // testing
        ++frames;
        if (frames > 50 && !played)
        {
            auto& animationComponent = Application::ApplicationManager::AppECS().GetComponentFor<Application::AnimatorComponent>(_animated);
            Application::ApplicationManager::AppAnimationManager().GetAnimator(animationComponent.animatorId).RepeatAnimation(Data::Ast.sanim.Monk_1_CharacterArmature_Run);
            played = true;
        }
        // \testing

        // testing
        Application::RotationComponent& entityRotationComponent = Application::ApplicationManager::AppECS().GetComponentFor<Application::RotationComponent>(_static);
        
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