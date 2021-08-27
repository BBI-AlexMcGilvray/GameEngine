#pragma once

#include <string>
#include <vector>

#include "Core/Math/Headers/Vector2.h"
#include "Core/Math/Headers/Vector3.h"
#include "Core/Math/Headers/Vector4.h"

#include "Data/Headers/AssetMacros.h"

namespace Data {
namespace Rendering {
  // holds the information about the mesh of a 3D object
  ASSET(AnimatedMeshData,
    (std::vector<Core::Math::Float3>) positions,
    (std::vector<Core::Math::Float3>) normals,
    (std::vector<Core::Math::Float2>) uvs,
    (std::vector<std::array<std::string, 4>>) boneNames,
    (std::vector<Core::Math::Float4>) boneWeights,
    (std::vector<Core::Math::Uint3>) indices,
    (uint) vertexCount
  );
  /*
  The runtime version of this data will need a 
  std::vector<AnimatedVertexDataBase> vertices
  that is made from all of the above (iterating over indices for iE[0, vertexCount) and making a AnimatedVertexDataBase from the position, and normal, uv, boneName, and boneWeight)
  */
}// namespace Rendering

  ASSET_TYPE(Rendering::AnimatedMeshData, "Resources/Meshes/", ".msh");
}// namespace Data