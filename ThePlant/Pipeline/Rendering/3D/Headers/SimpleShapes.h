#pragma once

#include "Core/Math/Headers/Vector3.h"

#include "Pipeline/Rendering/Mesh.h"

namespace Application {
namespace Rendering {
    void CreateLine(MeshData& mesh, const float& length);
    void CreateBox(MeshData& mesh, const Core::Math::Float3& dimensions);
    void CreateBox(MeshData& mesh, const Core::Math::Float3& min, const Core::Math::Float3& max);
    void CreatePyramid(MeshData& mesh, const float& height, const float& sideLength);
    void CreateSphere(MeshData& mesh, const float& radius);
} // namespace Rendering
} // namespace Application