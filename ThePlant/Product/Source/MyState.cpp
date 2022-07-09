#include "Product/Headers/MyState.h"

#include "Pipeline/Headers/ApplicationManager.h"

#include "Pipeline/StateSystem/Headers/StateHelpers.h"
#include "Pipeline/Physics/PhysicsSettings.h"

// testing
#include "Core/Random/Random.h"
#include "Core/Random/Functions.h"
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
: Application::State(applicationManager, 1024.0f, Application::Physics::Settings())
{}

void MyState::Initialize()
{
    Application::ECSSystemFlags activeSystems;
    activeSystems |= Application::ECSSystem::AnimationSystem;
    activeSystems |= Application::ECSSystem::CameraSystem;
    activeSystems |= Application::ECSSystem::CollisionSystem;
    activeSystems |= Application::ECSSystem::RenderingSystem;
    activeSystems |= Application::ECSSystem::TransformSystem;
    activeSystems |= Application::ECSSystem::PhysicsSystem;
    activeSystems |= Application::ECSSystem::VelocitySystem;
#if DEBUG
    activeSystems |= Application::ECSSystem::DebugBoneSystem;
    activeSystems |= Application::ECSSystem::DebugCollisionSystem;
    activeSystems |= Application::ECSSystem::DebugOctTreeSystem;
    activeSystems |= Application::ECSSystem::DebugTransformSystem;
#endif
    Application::SetECSSystems(*this, activeSystems);

    Application::CollisionHandlerFlags activeCollisionHandlers;
    activeCollisionHandlers |= Application::CollisionHandler::RigidBodyCollision;
#if DEBUG
    activeCollisionHandlers |= Application::CollisionHandler::DebugCollisionDisplay;
#endif
    Application::SetCollisionHandlers(*this, activeCollisionHandlers);

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
    // _static = Testing::SpawnStaticModel(*this);
    // _animated = Testing::SpawnAnimatedModel(*this);

    // Collision (to test it properly, may need to disable to transform debug systems (or shrink their size))
    _leftPos = Core::Math::Float3(-15.0f, 4.0f, -5.0f);
    _rightPos = Core::Math::Float3(15.0f, 4.0f, -5.0f);

    Core::Math::Float3 modifiedLeft = _leftPos + Core::Math::Float3(2.0f, 0.0f, 0.0f);
    Core::Math::Float3 modifiedRight = _rightPos + Core::Math::Float3(-2.0f, 0.0f, 0.0f);
    Core::Math::FQuaternion rotation1(0.0f, 0.0f, -0.707f, 0.707f); // pointing down (-90 rotation on z axis)
    Core::Math::FQuaternion rotation2(0.0f, 0.383f, 0.0f, 0.924f); // pointing horizontally in (90 rotation on y axis)

    _dir1 = true;
    _swapTime = Core::Second(15.0f);
    _currentSwap = _swapTime;
    // _collider = Testing::SpawnCollider(*this, Core::Math::Float3(5.0f, 0.0f, 0.0f), Core::Geometric::Sphere(), _leftPos, rotation1, 2.0f);
    // _trigger = Testing::SpawnTrigger(*this, Core::Math::Float3(-5.0f, 0.0f, 0.0f), Core::Geometric::Box(), _rightPos, rotation2, 2.0f);
    
    // Testing::SpawnStaticCollider(*this, Core::Geometric::Box(), Math::Lerp(modifiedLeft, modifiedRight, 0.2f));
    // Testing::SpawnStaticCollider(*this, Core::Geometric::Line3D(Core::Math::Float3(1.0f, 0.0f, 0.0f), false), Math::Lerp(modifiedLeft, modifiedRight, 0.4f));
    // Testing::SpawnStaticCollider(*this, Core::Geometric::Line3D(Core::Math::Float3(1.0f, 0.0f, 0.0f), false), Math::Lerp(_leftPos, _rightPos, 0.50f) + Core::Math::Float3(0.0f, 0.0f, 0.2f), rotation2);
    // Testing::SpawnStaticCollider(*this, Core::Geometric::Spot3D(), Math::Lerp(modifiedLeft, modifiedRight, 0.6f)); // works with: spot3D, sphere
    // Testing::SpawnStaticCollider(*this, Core::Geometric::Sphere(), Math::Lerp(modifiedLeft, modifiedRight, 0.8f), Core::Math::FQuaternion(Core::Math::II()), 2.0f); // works with: sphere, rotation2, 2.0f);
    /*
    * Try spawning a bunch of balls randomly with random speeds within the 'box' (maybe need a lid?)
    */
    Core::Random rand;
    int numSpawned = 1;
    for (int i = 0; i < numSpawned; ++i)
    {
        Core::Math::Float3 position = Math::Lerp(_leftPos, _rightPos, float(i) / static_cast<float>(numSpawned));
        Core::Math::Float3 velocity(Core::InRange(rand, -5.0f, 5.0f), Core::InRange(rand, -5.0f, 5.0f), 0.0f);
        Testing::SpawnCollider(*this, velocity, Core::Geometric::Sphere(), position);
    }

    // surrounding box
    /*
    * For some reason the sphere disappears on collision... why?
    */
    Core::Math::Float3 boundaryLeft = _leftPos + Core::Math::Float3(-2.0f, 0.0f, 0.0f);
    Core::Math::Float3 boundaryRight = _rightPos + Core::Math::Float3(2.0f, 0.0f, 0.0f);
    Core::Math::Float3 boundaryTop = Core::Math::Float3((_leftPos + _rightPos).XY * 0.5f, _leftPos.Z) + Core::Math::Float3(0.0f, 10.0f, 0.0f);
    Core::Math::Float3 boundaryBottom = Core::Math::Float3((_leftPos + _rightPos).XY * 0.5f, _leftPos.Z) - Core::Math::Float3(0.0f, 10.0f, 0.0f);
    Testing::SpawnStaticCollider(*this, Core::Geometric::Box(), boundaryLeft, Core::Math::FQuaternion(), Core::Math::Float3(1.0f, 20.0f, 1.0f));
    Testing::SpawnStaticCollider(*this, Core::Geometric::Box(), boundaryRight, Core::Math::FQuaternion(), Core::Math::Float3(1.0f, 20.0f, 1.0f));
    Testing::SpawnStaticCollider(*this, Core::Geometric::Box(), boundaryTop, Core::Math::FQuaternion(), Core::Math::Float3(40.0f, 1.0f, 1.0f));
    Testing::SpawnStaticCollider(*this, Core::Geometric::Box(), boundaryBottom, Core::Math::FQuaternion(), Core::Math::Float3(40.0f, 1.0f, 1.0f));

    // need to spawn some stuff to test the collision system
    // also, the physics collision handler is not working

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
    //     AnimationManager().GetAnimator(animationComponent.animatorId).RepeatAnimation(Data::Ast.sanim.Monk_1_CharacterArmature_Run);
    //     played = true;
    // }
    // \testing

    // testing (Static model)
    // Application::RotationComponent& entityRotationComponent = ECS().GetComponentFor<Application::RotationComponent>(_static);
    
    // FQuaternion entityRotation = entityRotationComponent.rotation;
    // FQuaternion newEntityRotation = Core::Math::LerpQuat(entityRotation, FQuaternion(0.0f, 0.1f, 0.0f, 0.9f) * entityRotation, Duration(dt));
    // entityRotationComponent.rotation = newEntityRotation;
    // \testing
}
}