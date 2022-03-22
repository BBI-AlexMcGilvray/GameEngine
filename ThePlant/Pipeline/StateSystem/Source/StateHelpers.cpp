#include "Pipeline/StateSystem/Headers/StateHelpers.h"

#include "Core/Debugging/Headers/Declarations.h"

#include "Pipeline/ECSSystems/AnimationSystem.h"
#include "Pipeline/ECSSystems/CameraSystem.h"
#include "Pipeline/ECSSystems/CollisionSystem.h"
#include "Pipeline/ECSSystems/TransformSystem.h"
#include "Pipeline/ECSSystems/RenderingSystem.h"
#if DEBUG
#include "Core/Debugging/Profiling/Utils.h"
#include "Pipeline/ECSSystems/DebugSystems/DebugBoneSystem.h"
#include "Pipeline/ECSSystems/DebugSystems/DebugCollisionSystem.h"
#include "Pipeline/ECSSystems/DebugSystems/DebugOctTreeSystem.h"
#include "Pipeline/ECSSystems/DebugSystems/DebugTransformSystem.h"
#endif

#include "Pipeline/Rendering/Headers/RenderManager.h"

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
    SetOrRemoveSystem<CameraSystem, TransformSystem>(stateECS, systems, ECSSystem::CameraSystem, state.RenderManager().GetCameraManager());
    SetOrRemoveSystem<CollisionSystem, TransformSystem>(stateECS, systems, ECSSystem::CollisionSystem, state.CollisionManager());
    SetOrRemoveSystem<RenderingSystem, TransformSystem, CameraSystem, AnimationSystem>(stateECS, systems, ECSSystem::RenderingSystem, state.RenderManager());
    SetOrRemoveSystem<TransformSystem, AnimationSystem>(stateECS, systems, ECSSystem::TransformSystem);
#if DEBUG
    SetOrRemoveSystem<DebugBoneSystem, TransformSystem>(stateECS, systems, ECSSystem::DebugBoneSystem, state.RenderManager(), state.ShaderManager());
    SetOrRemoveSystem<DebugCollisionSystem, CollisionSystem>(stateECS, systems, ECSSystem::DebugCollisionSystem, state.CollisionManager(), state.RenderManager(), state.ShaderManager());
    SetOrRemoveSystem<DebugOctTreeSystem, CollisionSystem>(stateECS, systems, ECSSystem::DebugOctTreeSystem, state.CollisionManager(), state.RenderManager(), state.ShaderManager());
    SetOrRemoveSystem<DebugTransformSystem, TransformSystem>(stateECS, systems, ECSSystem::DebugTransformSystem, state.RenderManager(), state.ShaderManager());
#endif
}
}// namespace Application