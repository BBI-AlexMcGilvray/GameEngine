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
#include "Product/Supplies/Assets.h"
#include "Product/Testing/TestingUtils.h"
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
        // _static = Testing::SpawnStaticModel(); // (Static model)
        // _animated = Testing::SpawnAnimatedModel(); // (Animated model)

        // Collision (to test it properly, may need to disable to transform debug systems (or shrink their size))
        _leftPos = Core::Math::Float3(-15.0f, 4.0f, 0.0f);
        _rightPos = Core::Math::Float3(15.0f, 4.0f, 0.0f);

        Core::Math::Float3 modifiedLeft = _leftPos + Core::Math::Float3(2.0f, 0.0f, 0.0f);
        Core::Math::Float3 modifiedRight = _rightPos + Core::Math::Float3(-2.0f, 0.0f, 0.0f);
        Core::Math::FQuaternion rotation1(0.0f, 0.0f, -0.707f, 0.707f); // pointing down (-90 rotation on z axis)
        Core::Math::FQuaternion rotation2(0.0f, 0.383f, 0.0f, 0.924f); // pointing horizontally in (90 rotation on y axis)

        _dir1 = true;
        _swapTime = Core::Second(5.0f);
        _currentSwap = _swapTime;
        _collider = Testing::SpawnCollider(Core::Geometric::Sphere(), _leftPos, rotation1, 2.0f);
        _trigger = Testing::SpawnTrigger(Core::Geometric::Box(), _rightPos, rotation2, 2.0f);
        
        Testing::SpawnCollider(Core::Geometric::Box(), Math::Lerp(modifiedLeft, modifiedRight, 0.2f));
        Testing::SpawnCollider(Core::Geometric::Line3D(1.0f), Math::Lerp(modifiedLeft, modifiedRight, 0.4f));
        // Testing::SpawnCollider(Core::Geometric::Line3D(1.0f), Math::Lerp(_leftPos, _rightPos, 0.50f) + Core::Math::Float3(0.0f, 0.0f, 0.2f), rotation2);
        Testing::SpawnCollider(Core::Geometric::Spot3D(), Math::Lerp(modifiedLeft, modifiedRight, 0.6f)); // works with: spot3D, sphere
        Testing::SpawnCollider(Core::Geometric::Sphere(), Math::Lerp(modifiedLeft, modifiedRight, 0.8f), Core::Math::FQuaternion(Core::Math::II()), 2.0f); // works with: sphere

        // do planes last
        // const auto modifiedLeft = _leftPos - Core::Math::Float3(0.0f, -2.0f, 0.0f);
        // const auto modifiedRight = _rightPos - Core::Math::Float3(0.0f, -2.0f, 0.0f);
        // Testing::SpawnCollider(Core::Geometric::Plane(), Math::Lerp(modifiedLeft, modifiedRight, 0.0f));
        // Testing::SpawnCollider(Core::Geometric::Plane(Core::Geometric::Circle()), Math::Lerp(modifiedLeft, modifiedRight, 0.2f));
        // Testing::SpawnCollider(Core::Geometric::Plane(Core::Geometric::Line2D()), Math::Lerp(modifiedLeft, modifiedRight, 0.4f));
        // Testing::SpawnCollider(Core::Geometric::Plane(Core::Geometric::Spot2D()), Math::Lerp(modifiedLeft, modifiedRight, 0.6f));
        // Testing::SpawnCollider(Core::Geometric::Plane(Core::Geometric::Rectangle()), Math::Lerp(modifiedLeft, modifiedRight, 0.8f));

        // Tested combinations:
        /*
         ** Also need to test scaling!
                       | Rot | Not| Rot | Not| Rot | Not| Rot | Not|
                       |   Box    |   Line3D  |   Spot3D  | Sphere   |
            Box     Rot|     |    |     |     |     |     |     |    |
                    Not|     |    |     |     |     |     |     |    |

            Line3D  Rot|     |    |  Y  |  Y  |     |  Y  |     |    |
                    Not|     |    |  Y  |  Y  |     |  Y  |     |    |

            Spot3D  Rot|     |    |     |     |     |     |     |    |
                    Not|     |    |  Y  |  Y  |     |  Y  |     |    |

            Sphere  Rot|     |    |     |     |     |     |     |    |
                    Not|     |    |     |     |     |     |     |    |

            ~~Plane do later
        */
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

        // testing (Animated model)
        // ++frames;
        // if (frames > 50 && !played)
        // {
        //     auto& animationComponent = Application::ApplicationManager::AppECS().GetComponentFor<Application::AnimatorComponent>(_animated);
        //     Application::ApplicationManager::AppAnimationManager().GetAnimator(animationComponent.animatorId).RepeatAnimation(Data::Ast.sanim.Monk_1_CharacterArmature_Run);
        //     played = true;
        // }
        // \testing

        // testing (Static model)
        // Application::RotationComponent& entityRotationComponent = Application::ApplicationManager::AppECS().GetComponentFor<Application::RotationComponent>(_static);
        
        // FQuaternion entityRotation = entityRotationComponent.rotation;
        // FQuaternion newEntityRotation = Core::Math::LerpQuat(entityRotation, FQuaternion(0.0f, 0.1f, 0.0f, 0.9f) * entityRotation, Duration(dt));
        // entityRotationComponent.rotation = newEntityRotation;
        // \testing

        // testing (Collision)
        auto& colliderPos = Application::ApplicationManager::AppECS().GetComponentFor<Application::PositionComponent>(_collider);
        auto& triggerPos = Application::ApplicationManager::AppECS().GetComponentFor<Application::PositionComponent>(_trigger);

        _currentSwap -= dt;
        colliderPos = Math::Lerp(_dir1 ? _leftPos : _rightPos, _dir1 ? _rightPos : _leftPos, Duration(_currentSwap) / Duration(_swapTime));
        triggerPos = Math::Lerp(_dir1 ? _rightPos : _leftPos, _dir1 ? _leftPos : _rightPos, Duration(_currentSwap) / Duration(_swapTime));
        if (_currentSwap <= Core::Second(0.0f))
        {
            _dir1 = !_dir1;
            _currentSwap = _swapTime;
        }
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