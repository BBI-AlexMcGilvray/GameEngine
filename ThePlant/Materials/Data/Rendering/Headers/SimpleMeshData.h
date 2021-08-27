#pragma once

#include <vector>

#include "Core/Math/Headers/Vector2.h"
#include "Core/Math/Headers/Vector3.h"
#include "Core/Math/Headers/Vector4.h"

#include "Data/Headers/AssetMacros.h"

namespace Data {
namespace Rendering {
  // holds the information about the mesh of a 3D object
  ASSET(SimpleMeshData,
    (std::vector<Core::Math::Float3>) positions,
    (std::vector<Core::Math::Float3>) normals,
    (std::vector<Core::Math::Uint3>) indices,
    (uint) vertexCount
  );
}// namespace Rendering

ASSET_TYPE(Rendering::SimpleMeshData, "Resources/Meshes/", ".msh");
}// namespace Data