#pragma once

#include <vector>

#include "Pipeline/ECS/DataOriented/Systems/System.h"
#include "Pipeline/ECSSystems/CameraComponents.h"
#include "Pipeline/ECSSystems/TransformComponents.h"
#include "Pipeline/Rendering/Headers/CameraManager.h"
#include "Pipeline/Rendering/Headers/CameraUtils.h"

#include "Core/Debugging/Profiling/Utils.h"

namespace Application {
struct CameraSystem : public System<CameraSystem>
{
    CameraSystem(Rendering::CameraManager& cameraManager)
    : System<CameraSystem>("CameraSystem")
    , _cameraManager(cameraManager)
    {}
    
    Core::runtimeId_t GetSystem() const { return Core::GetTypeId<CameraSystem>(); };

    void Execute(ArchetypeManager& archetypeManager) const override
    {
        DEBUG_PROFILE_SCOPE(GetSystemName());

        _cameraManager.ClearCameras();
        
        std::vector<Core::Ptr<Archetype>> affectedArchetypes = archetypeManager.GetArchetypesContaining<CameraComponent, WorldTransformComponent>();

        for (auto& archetype : affectedArchetypes)
        {
            _ApplyToArchetype(_cameraManager, archetype->GetComponents<CameraComponent>(), archetype->GetComponents<WorldTransformComponent>());
        }
    }

private:
    Rendering::CameraManager& _cameraManager;
    
    // need this to ensure none of the affected archetypes have a CameraWeightingComponent
    static void _ApplyToArchetype(Rendering::CameraManager& cameraManager, std::vector<CameraComponent>& cameras, std::vector<WorldTransformComponent>& transforms)
    {
        DEBUG_ASSERT(cameras.size() == transforms.size());
        for (size_t index = 0; index < cameras.size(); ++index)
        {
            Rendering::LookAt(transforms[index].transform, cameras[index].targetPosition);
            cameraManager.AddCamera(CalculateTransformationMatrix(cameras[index].camera, transforms[index].transform));
        }
    }
};

// struct WeightedCameraSystem : public System<WeightedCameraSystem, CameraComponent, CameraWeightingComponent, WorldTransformComponent>
// {
//     WeightedCameraSystem(Rendering::CameraManager& cameraManager)
//     : _cameraManager(cameraManager)
//     {}

//     static void ApplyToArchetype(std::vector<CameraComponent>& cameras, std::vector<CameraComponent>& weightings, std::vector<WorldTransformComponent>& transforms)
//     {
//         DEBUG_ASSERT(cameras.size() == weightings.size() == transforms.size());
//         for (size_t index = 0; index < cameras.size(); ++index)
//         {
//             // we need to calculate the final camera for each component group and then add that final camera to the manager instead
//             _cameraManager.AddCamera(CalculateTransformationMatrix(cameras[index].camera, transforms[index].transform));
//         }
//     }

// private:
//     Rendering::CameraManager& _cameraManager;
// };
} // namespace Application