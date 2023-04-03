#include "Pipeline/StateSystem/Headers/StateHelpers.h"

#include "Pipeline/Physics/PhysicsCollisionHandler.h"
#include "Pipeline/ECSSystems/AnimationSystem.h"
#include "Pipeline/ECSSystems/CameraSystem.h"
#include "Pipeline/ECSSystems/CollisionSystem.h"
#include "Pipeline/ECSSystems/LifetimeSystem.h"
#include "Pipeline/ECSSystems/TransformSystem.h"
#include "Pipeline/ECSSystems/RenderingSystem.h"
#include "Pipeline/Physics/PhysicsSystem.h"
#include "Pipeline/Physics/VelocitySystem.h"
#if DEBUG
#include "Core/Debugging/Profiling/Utils.h"
#include "Pipeline/Collision/CollisionHandlers/DebugHandlers/DebugCollisionDisplay.h"
#include "Pipeline/ECSSystems/DebugSystems/DebugBoneSystem.h"
#include "Pipeline/ECSSystems/DebugSystems/DebugCollisionSystem.h"
#include "Pipeline/ECSSystems/DebugSystems/DebugOctTreeSystem.h"
#include "Pipeline/ECSSystems/DebugSystems/DebugTransformSystem.h"
#endif

#include "Pipeline/Rendering/Headers/RenderManager.h"
#include "Pipeline/Rendering/DefaultRenderLayers.h"

namespace Application {
void SetSystemState(ECSSystemFlags& systems, const ECSSystem& system, const bool& active)
{
    if (active)
    {
        systems |= system;
    }
    else
    {
        systems ^= system;
    }
}

bool GetSystemState(const ECSSystemFlags& systems, const ECSSystem& system)
{
    return systems.AtLeastOneFlag(system);
}

template <typename SYSTEM, typename ...DEPENDENCIES, typename ...ARGS>
void SetOrRemoveSystem(ECS& ecs, const ECSSystemFlags& systems, const ECSSystem& system, ARGS&& ...args)
{
    if (GetSystemState(systems, system))
    {
        ecs.AddSystem<SYSTEM>(std::forward<ARGS>(args)...).AddDependencies<DEPENDENCIES...>();
    }
    else
    {
        ecs.RemoveSystem<SYSTEM>();
    }
}

void SetECSSystems(State& state, const ECSSystemFlags& systems)
{
    ECS& stateECS = state.ECS();

    SetOrRemoveSystem<AnimationSystem>(stateECS, systems, ECSSystem::AnimationSystem, state.AnimationManager());
    SetOrRemoveSystem<VelocitySystem>(stateECS, systems, ECSSystem::VelocitySystem, state.TimeSystem());
    SetOrRemoveSystem<PhysicsSystem, VelocitySystem>(stateECS, systems, ECSSystem::PhysicsSystem, state.TimeSystem(), state.PhysicsSettings());
    SetOrRemoveSystem<TransformSystem, AnimationSystem, PhysicsSystem, VelocitySystem>(stateECS, systems, ECSSystem::TransformSystem);
    SetOrRemoveSystem<CameraSystem, TransformSystem>(stateECS, systems, ECSSystem::CameraSystem, state.RenderManager().GetCameraManager());
    SetOrRemoveSystem<CollisionSystem, TransformSystem>(stateECS, systems, ECSSystem::CollisionSystem, state.CollisionManager());
    SetOrRemoveSystem<RenderingSystem, TransformSystem, CameraSystem, AnimationSystem>(stateECS, systems, ECSSystem::RenderingSystem, state.RenderManager());
    SetOrRemoveSystem<LifetimeSystem>(stateECS, systems, ECSSystem::LifetimeSystem, state.TimeSystem());
#if DEBUG
    SetOrRemoveSystem<DebugBoneSystem, TransformSystem>(stateECS, systems, ECSSystem::DebugBoneSystem, state.RenderManager(), state.MaterialManager(), state.MeshManager());
    SetOrRemoveSystem<DebugCollisionSystem, CollisionSystem>(stateECS, systems, ECSSystem::DebugCollisionSystem, state.CollisionManager(), state.RenderManager(), state.MaterialManager(), state.MeshManager());
    SetOrRemoveSystem<DebugOctTreeSystem, CollisionSystem>(stateECS, systems, ECSSystem::DebugOctTreeSystem, state.CollisionManager(), state.RenderManager(), state.MaterialManager(), state.MeshManager());
    SetOrRemoveSystem<DebugTransformSystem, TransformSystem>(stateECS, systems, ECSSystem::DebugTransformSystem, state.RenderManager(), state.MaterialManager(), state.MeshManager());
#endif
}

void SetCollisionHandlerState(CollisionHandlerFlags& handlers, const CollisionHandler& handler, const bool& active)
{
    if (active)
    {
        handlers |= handler;
    }
    else
    {
        handlers ^= handler;
    }
}

bool GetCollisionHandlerState(const CollisionHandlerFlags& handlers, const CollisionHandler& handler)
{
    return handlers.AtLeastOneFlag(handler);
}

template <typename HANDLER, typename ...ARGS>
void SetOrRemoveCollisionHandler(Collision::CollisionManager& collisionManager, const CollisionHandlerFlags& handlers, const CollisionHandler& handler, ARGS&& ...args)
{
    if (GetCollisionHandlerState(handlers, handler))
    {
        collisionManager.AddCollisionHandler<HANDLER>(std::forward<ARGS>(args)...);// collision handlers do not have dependencies (should they?) .AddDependencies<DEPENDENCIES...>();
    }
    else
    {
        collisionManager.RemoveCollisionHandler<HANDLER>();
    }
}

void SetCollisionHandlers(State& state, const CollisionHandlerFlags& handlers)
{
    Collision::CollisionManager& collisionManager = state.CollisionManager();

    SetOrRemoveCollisionHandler<Collision::RigidBodyCollision>(collisionManager, handlers, CollisionHandler::RigidBodyCollision);
#if DEBUG
    SetOrRemoveCollisionHandler<Collision::DebugCollisionDisplay>(collisionManager, handlers, CollisionHandler::DebugCollisionDisplay, state.RenderManager(), state.MaterialManager(), state.MeshManager());
#endif
}

void SetRenderLayerState(RenderLayerFlags& layers, const RenderLayer& layer, const bool& active)
{
    if (active)
    {
        layers |= layer;
    }
    else
    {
        layers ^= layer;
    }
}

bool GetRenderLayerState(const RenderLayerFlags& layers, const RenderLayer& layer)
{
    return layers.AtLeastOneFlag(layer);
}

void SetRenderLayers(State& state, const RenderLayerFlags& layers)
{
    Rendering::RenderManager& renderManager = state.RenderManager();

    renderManager.AddLayer<Rendering::DefaultRenderLayer>();
#if DEBUG
    renderManager.AddLayer<Rendering::DebugRenderLayer>().AddDependency<Rendering::DefaultRenderLayer>();
#endif
}
}// namespace Application