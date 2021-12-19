#pragma once

#include "Core/Math/Headers/Vector2.h"

#include "Pipeline/Rendering/Mesh_NEW.h"

namespace Application {
namespace Rendering {
    Mesh_NEW CreateBox(const Core::Math::Float2& dimensions);
    Mesh_NEW CreateBox(const Core::Math::Float2& min, const Core::Math::Float2& max);
    Mesh_NEW CreateCircle(const float& radius);
} // namespace Rendering
} // namespace Application