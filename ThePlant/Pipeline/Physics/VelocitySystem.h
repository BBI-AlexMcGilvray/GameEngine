#pragma once

#include <vector>

#include "Core/Headers/TimeDefs.h"
#include "Core/Debugging/Profiling/Utils.h"

#include "Pipeline/ECS/DataOriented/Systems/DeltaTimeSystem.h"
#include "Pipeline/ECSSystems/TransformComponents.h"
#include "Pipeline/Physics/PhysicsComponents.h"
#include "Pipeline/Physics/PhysicsSettings.h"

namespace Application {
struct VelocitySystem : public DeltaTimeSystem<VelocitySystem, VelocityComponent, PositionComponent>
{
    VelocitySystem(const Time::TimeSystem& timeSystem)
    : DeltaTimeSystem<VelocitySystem, VelocityComponent, PositionComponent>("VelocitySystem", timeSystem)
    {}

    static void ApplyToArchetype(const Core::Second& deltaTime, const std::vector<VelocityComponent>& velocities, std::vector<PositionComponent>& positions)
    {
        for (size_t index = 0; index < velocities.size(); ++index)
        {
            positions[index].position += velocities[index].velocity * static_cast<float>(Core::Duration(deltaTime));
        }
    }
};
} // namespace Application