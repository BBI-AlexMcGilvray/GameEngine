#pragma once

#include "Core/Math/Headers/Vector3.h"

#include "Pipeline/Rendering/Mesh.h"

namespace Application {
namespace Rendering {
    Mesh CreateBox(const Core::Math::Float3& dimensions);
    Mesh CreateBox(const Core::Math::Float3& min, const Core::Math::Float3& max);
    Mesh CreatePyramid(const float& height, const float& sideLength);
    Mesh CreateSphere(const float& radius);
} // namespace Rendering
} // namespace Application