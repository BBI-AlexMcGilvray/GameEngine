#pragma once

#include "Core/Math/Headers/Vector3.h"

#include "Pipeline/Rendering/Mesh_NEW.h"

namespace Application {
namespace Rendering {
    Mesh_NEW CreateCube(const Core::Math::Float3& dimensions);
    Mesh_NEW CreateCube(const Core::Math::Float3& min, const Core::Math::Float3& max);
    Mesh_NEW CreateSphere(const float& radius);
} // namespace Rendering
} // namespace Application