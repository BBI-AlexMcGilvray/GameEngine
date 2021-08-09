#pragma once

#include <vector>

#include "Data/Headers/AssetMacros.h"
#include "Data/Rendering/Headers/VertexBaseData.h"

namespace Data {
namespace Rendering {
  // holds the information about the mesh of a 3D object
  ASSET(SimpleMeshData,
    (std::vector<SimpleVertexDataBase>) vertices,
    (uint) vertexCount
  );
  /*
  Currently, by storing the data as an array of SimpleVertexDataBase's we inflate the size of the data when stored (due to duplicates).
  Leaving it as-is for now to get things working, but will need to update at a later date (maybe a custom deserializer)
  */
}// namespace Rendering

ASSET_TYPE(Rendering::SimpleMeshData, "Resources/Meshes/", ".msh");
}// namespace Data