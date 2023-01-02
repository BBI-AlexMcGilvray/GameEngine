#pragma once

#include "Core/Reflection/Reflectable.h"
#include "Core/IdTypes/IncrementalId.h"
#include "Core/Math/Headers/Vector2.h"

#include "Pipeline/Rendering/Headers/Camera.h"

namespace Application {
struct CameraComponent
{
    // should this have the camera id used by the render camera?
    REFLECTABLE(
        (Rendering::Camera) camera,
        (Core::Math::Int2) renderDimensions
    )

    CameraComponent() = default;
    CameraComponent(const CameraComponent&) = default;
    CameraComponent(CameraComponent&&) = default;
    CameraComponent& operator=(const CameraComponent&) = default;
    CameraComponent& operator=(CameraComponent&&) = default;

    CameraComponent(Rendering::Camera&& camera, const Core::Math::Int2& renderDimensions)
    : camera(std::move(camera))
    , renderDimensions(renderDimensions)
    {}

    bool operator==(const CameraComponent& other) const
    {
        return camera == other.camera && renderDimensions == other.renderDimensions;
    }
    bool operator !=(const CameraComponent& other) const { return !(*this == other); }
};

struct CameraWeightingComponent
{
    REFLECTABLE(
        (float) weight
    )
    IncrementalId cameraGroup; // this should be recalculated every time, so we should save a name or tag for the camera group instead?

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