#pragma once

#include "Pipeline/ECS/DataOriented/Systems/System.h"
#include "Pipeline/ECSSystems/TransformComponents.h"

namespace Application {
struct WorldTransformSystem : public System<WorldTransformSystem>
{
    // how do we make sure we are only affecting entities with the WorldTransformComponent and NOT any of the other components?
    static void ApplyToArchetype(std::vector<WorldTransformSystem>& worldTransforms)
    {

    }
};

struct TransformSystem : public CompoundSystem<TransformSystem, WorldTransformSystem>
{
    // no need for application logic, it is handled by the CompoundSystem class
};
}// namespace Application