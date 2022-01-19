#pragma once

#include "Core/Math/Headers/Vector2.h"

#include "Pipeline/Rendering/Mesh.h"

namespace Application {
namespace Rendering {
    Mesh CreateRectangle(const Core::Math::Float2& dimensions);
    Mesh CreateRectangle(const Core::Math::Float2& min, const Core::Math::Float2& max);
    Mesh CreateCircle(const float& radius);
} // namespace Rendering
} // namespace Application