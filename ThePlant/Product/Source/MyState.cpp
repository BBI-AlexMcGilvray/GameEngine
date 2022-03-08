#include "Product/Headers/MyState.h"

#include "Pipeline/Headers/ApplicationManager.h"

#include "Pipeline/StateSystem/Headers/StateHelpers.h"

// testing
#include "Core/Math/Headers/UtilityFunctions.h"
#include "Core/Math/Headers/MatrixFunctions.h"

#include "Pipeline/Collision/CollisionHandlers/DebugHandlers/DebugCollisionDisplay.h"
#include "Pipeline/ECSSystems/AnimationComponents.h"
#include "Pipeline/ECSSystems/CameraComponents.h"
#include "Pipeline/ECSSystems/ColliderComponents.h"

#include "Product/Supplies/Assets.h"
#include "Product/Testing/TestingUtils.h"
// \testing

namespace Product
{
MyState::MyState(Application::ApplicationManager& applicationManager)
: Application::State(applicationManager, 1024.0f)
{}

void MyState::Initialize()
{
    Application::ECSSystemFlags activeSystems;
    activeSystems |= Application::ECSSystem::AnimationSystem;
    activeSystems |= Application::ECSSystem::CameraSystem;
    activeSystems |= Application::ECSSystem::CollisionSystem;
    activeSystems |= Application::ECSSystem::RenderingSystem;
    activeSystems |= Application::ECSSystem::TransformSystem;
#if DEBUG
    activeSystems |= Application::ECSSystem::DebugBoneSystem;
    activeSystems |= Application::ECSSystem::DebugCollisionSystem;
    activeSystems |= Application::ECSSystem::DebugOctTreeSystem;
    activeSystems |= Application::ECSSystem::DebugTransformSystem;
#endif
    Application::SetECSSystems(*this, activeSystems);

    // collision manager should have helpers like the above for systems
    _collisionManager.AddCollisionHandler<Application::Collision::DebugCollisionDisplay>(RenderManager(), ShaderManager());

    // this will be data driven from the future
    // create camera
    Core::Geometric::Transform cameraTransform;
    Application::CameraComponent camera(1280.0f / 1080.0f, Core::Math::Float3(0.0f, 0.0f, 0.0f));
    auto cameraComponents = std::make_tuple<Application::CameraComponent, Application::WorldTransformComponent, Application::PositionComponent, Application::RotationComponent>(std::move(camera), cameraTransform, Core::Math::Float3(0.0f, 0.0f, 20.0f), Core::Math::FQuaternion(Core::Math::II()));
    _camera = ECS().CreateEntity(cameraComponents);

    // create camera controller
    _cameraController = CameraController(ECS(), _camera.GetEntityId());
    Application::Input::InputManager& inputManager = InputManager();
    inputManager.setInputController<Application::Input::DefaultInputController>();
    inputManager->addReceiver(&_cameraController);

    // testing
    // _static = Testing::SpawnStaticModel(*this); // (Static model)
    // _animated = Testing::SpawnAnimatedModel(*this); // (Animated model)

    // Collision (to test it properly, may need to disable to transform debug systems (or shrink their size))
    _leftPos = Core::Math::Float3(-15.0f, 4.0f, 0.0f);
    _rightPos = Core::Math::Float3(15.0f, 4.0f, 0.0f);

    Core::Math::Float3 modifiedLeft = _leftPos + Core::Math::Float3(2.0f, 0.0f, 0.0f);
    Core::Math::Float3 modifiedRight = _rightPos + Core::Math::Float3(-2.0f, 0.0f, 0.0f);
    Core::Math::FQuaternion rotation1(0.0f, 0.0f, -0.707f, 0.707f); // pointing down (-90 rotation on z axis)
    Core::Math::FQuaternion rotation2(0.0f, 0.383f, 0.0f, 0.924f); // pointing horizontally in (90 rotation on y axis)

    _dir1 = true;
    _swapTime = Core::Second(15.0f);
    _currentSwap = _swapTime;
    _collider = Testing::SpawnCollider(*this, Core::Geometric::Sphere(), _leftPos, rotation1, 2.0f);
    _trigger = Testing::SpawnTrigger(*this, Core::Geometric::Box(), _rightPos, rotation2, 2.0f);
    
    Testing::SpawnStaticCollider(*this, Core::Geometric::Box(), Math::Lerp(modifiedLeft, modifiedRight, 0.2f));
    Testing::SpawnStaticCollider(*this, Core::Geometric::Line3D(Core::Math::Float3(1.0f, 0.0f, 0.0f), false), Math::Lerp(modifiedLeft, modifiedRight, 0.4f));
    Testing::SpawnStaticCollider(*this, Core::Geometric::Line3D(Core::Math::Float3(1.0f, 0.0f, 0.0f), false), Math::Lerp(_leftPos, _rightPos, 0.50f) + Core::Math::Float3(0.0f, 0.0f, 0.2f), rotation2);
    Testing::SpawnStaticCollider(*this, Core::Geometric::Spot3D(), Math::Lerp(modifiedLeft, modifiedRight, 0.6f)); // works with: spot3D, sphere
    Testing::SpawnStaticCollider(*this, Core::Geometric::Sphere(), Math::Lerp(modifiedLeft, modifiedRight, 0.8f), Core::Math::FQuaternion(Core::Math::II()), 2.0f); // works with: sphere

    // do planes last
    // const auto modifiedLeft = _leftPos - Core::Math::Float3(0.0f, -2.0f, 0.0f);
    // const auto modifiedRight = _rightPos - Core::Math::Float3(0.0f, -2.0f, 0.0f);
    // Testing::SpawnCollider(*this, Core::Geometric::Plane(), Math::Lerp(modifiedLeft, modifiedRight, 0.0f));
    // Testing::SpawnCollider(*this, Core::Geometric::Plane(Core::Geometric::Circle()), Math::Lerp(modifiedLeft, modifiedRight, 0.2f));
    // Testing::SpawnCollider(*this, Core::Geometric::Plane(Core::Geometric::Line2D()), Math::Lerp(modifiedLeft, modifiedRight, 0.4f));
    // Testing::SpawnCollider(*this, Core::Geometric::Plane(Core::Geometric::Spot2D()), Math::Lerp(modifiedLeft, modifiedRight, 0.6f));
    // Testing::SpawnCollider(*this, Core::Geometric::Plane(Core::Geometric::Rectangle()), Math::Lerp(modifiedLeft, modifiedRight, 0.8f));

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

void MyState::Start()
{
    // auto& animationComponent = Application::ApplicationManager::AppECS().GetComponentFor<Application::AnimatorComponent>(_woman);
    // Application::ApplicationManager::AppAnimationManager().GetAnimator(animationComponent.animatorId).PlayAnimation(Data::Ast.sanim.Monk_1_CharacterArmature_Idle);    
}

void MyState::End() {};
void MyState::CleanUp() {};

// testing
bool played = false;
int frames = 0;
// \testing
void MyState::_PreECSUpdate(Second dt) {};
void MyState::_PostECSUpdate(Second dt)
{
    // testing (Animated model)
    // ++frames;
    // if (frames > 50 && !played)
    // {
    //     auto& animationComponent = ECS().GetComponentFor<Application::AnimatorComponent>(_animated);
    //     Application::ApplicationManager::AppAnimationManager().GetAnimator(animationComponent.animatorId).RepeatAnimation(Data::Ast.sanim.Monk_1_CharacterArmature_Run);
    //     played = true;
    // }
    // \testing

    // testing (Static model)
    // Application::RotationComponent& entityRotationComponent = ECS().GetComponentFor<Application::RotationComponent>(_static);
    
    // FQuaternion entityRotation = entityRotationComponent.rotation;
    // FQuaternion newEntityRotation = Core::Math::LerpQuat(entityRotation, FQuaternion(0.0f, 0.1f, 0.0f, 0.9f) * entityRotation, Duration(dt));
    // entityRotationComponent.rotation = newEntityRotation;
    // \testing

    // testing (Collision)
    auto& colliderPos = ECS().GetComponentFor<Application::PositionComponent>(_collider);
    auto& triggerPos = ECS().GetComponentFor<Application::PositionComponent>(_trigger);

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
}