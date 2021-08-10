#pragma once

#include <vector>

#include "Data/Headers/AssetMacros.h"
#include "Data/Rendering/Headers/VertexBaseData.h"

namespace Data {
namespace Rendering {
  // holds the information about the mesh of a 3D object
  ASSET(SimpleMeshData,
    (std::vector<Core::Math::Float3>) positions,
    (std::vector<Core::Math::Float3>) normals,
    (std::vector<Core::Math::Uint3>) indices,
    (uint) vertexCount
  );
  /*
  The runtime version of this data will need a 
  std::vector<SimpleVertexDataBase> vertices
  that is made from all of the above (iterating over indices for iE[0, vertexCount) and making a SimpleVertexDataBase from the position, and normal)
  */
}// namespace Rendering

ASSET_TYPE(Rendering::SimpleMeshData, "Resources/Meshes/", ".msh");
}// namespace Data