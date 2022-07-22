#pragma once

#include "Pipeline/Rendering/Headers/Camera.h"

namespace Application {
struct CameraComponent
{
    Rendering::Camera camera;

    CameraComponent() = default;
    CameraComponent(const CameraComponent&) = default;
    CameraComponent(CameraComponent&&) = default;
    CameraComponent& operator=(const CameraComponent&) = default;
    CameraComponent& operator=(CameraComponent&&) = default;

    CameraComponent(const Rendering::Camera& camera)
    : camera(camera)
    {}

    bool operator==(const CameraComponent& other) const
    {
        return camera == other.camera;
    }
    bool operator !=(const CameraComponent& other) const { return !(*this == other); }
};

struct CameraWeightingComponent
{
    float weight;
    IncrementalId cameraGroup;

    CameraWeightingComponent() = default;
    CameraWeightingComponent(const CameraWeightingComponent&) = default;
    CameraWeightingComponent(CameraWeightingComponent&&) = default;
    CameraWeightingComponent& operator=(const CameraWeightingComponent&) = default;
    CameraWeightingComponent& operator=(CameraWeightingComponent&&) = default;

    CameraWeightingComponent(const float& weight, const IncrementalId& cameraGroup)
    : weight(weight)
    , cameraGroup(cameraGroup)
    {}

    bool operator==(const CameraWeightingComponent& other) const
    {
        return weight == other.weight;
    }
    bool operator !=(const CameraWeightingComponent& other) const { return !(*this == other); }
};
}// namespace Application