#pragma once

#include "Core/Debugging/Profiling/Utils.h"
#include "Core/Math/Headers/Vector4.h"
#include "Core/Geometric/Line3D.h"

#include "Pipeline/Collision/CollisionManager.h"
#include "Pipeline/ECS/DataOriented/ECS.h"
#include "Pipeline/ECS/DataOriented/EntityHandler.h"
#include "Pipeline/ECS/DataOriented/EntitySnapshot.h"
#include "Pipeline/Input/Headers/InputState.h"
#include "Pipeline/StateSystem/Headers/State.h"

namespace Application
{
namespace Collision
{
    // -1 lifetime -> no lifetime
    EntityHandler& CreateRay(ECS& ecs, const Core::Math::Float3& origin, const Core::Geometric::Line3D& ray, const float& lifetime = -1.0f);
    Core::Geometric::Line3D GetClickRayForCamera(State& state, const Application::Input::AxisState& mouseState, const EntitySnapshot& cameraState);

    std::pair<EntitySnapshot, Core::Geometric::Point3D> GetFirstRaycastHit(State& state, const Core::Math::Float3& origin, const Core::Geometric::Line3D& ray);    
    std::vector<std::pair<EntitySnapshot, Core::Geometric::Point3D>> GetAllRaycastHits(State& state, const Core::Math::Float3& origin, const Core::Geometric::Line3D& ray);

    std::pair<EntitySnapshot, Core::Geometric::Point3D> GetFirstClickedOn(State& state, const Application::Input::AxisState& mouseState, const EntitySnapshot& cameraState);
    std::vector<std::pair<EntitySnapshot, Core::Geometric::Point3D>> GetAllClickedOn(State& state, const Application::Input::AxisState& mouseState, const EntitySnapshot& cameraState);

#if DEBUG
    std::pair<EntitySnapshot, Core::Geometric::Point3D> GetFirstRaycastHitAndCreateRay(State& state, const Core::Math::Float3& origin, const Core::Geometric::Line3D& ray, const float& lifetime = -1.0f);
    std::vector<std::pair<EntitySnapshot, Core::Geometric::Point3D>> GetAllRaycastHitsAndCreateRay(State& state, const Core::Math::Float3& origin, const Core::Geometric::Line3D& ray, const float& lifetime = -1.0f);

    std::pair<EntitySnapshot, Core::Geometric::Point3D> GetFirstClickedOnAndCreateRay(State& state, const Application::Input::AxisState& mouseState, const EntitySnapshot& cameraState, const float& lifetime = -1.0f);
    std::vector<std::pair<EntitySnapshot, Core::Geometric::Point3D>> GetAllClickedOnAndCreateRay(State& state, const Application::Input::AxisState& mouseState, const EntitySnapshot& cameraState, const float& lifetime = -1.0f);
#endif //DEBUG
} // namespace Collision
} // namespace Application