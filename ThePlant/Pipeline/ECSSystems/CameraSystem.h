#pragma once

#include <vector>

#include "Pipeline/ECS/DataOriented/Systems/System.h"
#include "Pipeline/ECSSystems/CameraComponents.h"
#include "Pipeline/ECSSystems/TransformComponents.h"
#include "Pipeline/Rendering/Headers/CameraManager.h"
#include "Pipeline/Rendering/Headers/CameraUtils.h"

namespace Application {
struct CameraSystem : public System<CameraSystem, CameraComponent, WorldTransformComponent>
{
    CameraSystem(Rendering::CameraManager& cameraManager)
    : _cameraManager(cameraManager)
    {}

    // need this to ensure none of the affected archetypes have a CameraWeightingComponent
    static void ApplyToArchetype(std::vector<CameraComponent>& cameras, std::vector<WorldTransformComponent>& transforms)
    {
        VERIFY(cameras.size() == transforms.size());
        for (size_t index = 0; index < cameras.size(); ++index)
        {
            _cameraManager.AddCamera(CalculateTransformationMatrix(cameras[index].camera, transforms[index].transform));
        }
    }

private:
    Rendering::CameraManager& _cameraManager;
};

struct WeightedCameraSystem : public System<WeightedCameraSystem, CameraComponent, CameraWeightingComponent, WorldTransformComponent>
{
    WeightedCameraSystem(Rendering::CameraManager& cameraManager)
    : _cameraManager(cameraManager)
    {}

    static void ApplyToArchetype(std::vector<CameraComponent>& cameras, std::vector<CameraComponent>& weightings, std::vector<WorldTransformComponent>& transforms)
    {
        VERIFY(cameras.size() == weightings.size() == transforms.size());
        for (size_t index = 0; index < cameras.size(); ++index)
        {
            // we need to calculate the final camera for each component group and then add that final camera to the manager instead
            _cameraManager.AddCamera(CalculateTransformationMatrix(cameras[index].camera, transforms[index].transform));
        }
    }

private:
    Rendering::CameraManager& _cameraManager;
};
} // namespace Application