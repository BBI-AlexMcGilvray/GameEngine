#pragma once

#include <vector>

#include "Core/Headers/CoreDefs.h"

#include "Data/Headers/AssetMacros.h"
#include "Data/Rendering/Headers/VertexBaseData.h"

namespace Data {
namespace Rendering {
  // holds the information about the mesh of a 3D object
  ASSET(StaticMeshData,
    (std::vector<Core::Math::Float3>) positions,
    (std::vector<Core::Math::Float3>) normals,
    (std::vector<Core::Math::Float2>) uvs,
    (std::vector<Core::Math::Uint3>) indices,
    (uint) vertexCount
  );
  /*
  The runtime version of this data will need a 
  std::vector<VertexDataBase> vertices
  that is made from all of the above (iterating over indices for iE[0, vertexCount) and making a VertexDataBase from the position, normal, and uv)
  */
}// namespace Rendering

ASSET_TYPE(Rendering::StaticMeshData, "Resources/Meshes/", ".msh");
}// namespace Data