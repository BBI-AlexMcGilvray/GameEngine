#pragma once

#include "Core/Math/Headers/Vector2.h"

#include "Pipeline/Rendering/Mesh.h"

namespace Application {
namespace Rendering {
    void CreateRectangle(MeshData& mesh, const Core::Math::Float2& dimensions);
    void CreateRectangle(MeshData& mesh, const Core::Math::Float2& min, const Core::Math::Float2& max);
    void CreateCircle(MeshData& mesh, const float& radius);
} // namespace Rendering
} // namespace Application