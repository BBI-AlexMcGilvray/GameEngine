#pragma once

#include <vector>

#include "Data/Headers/AssetMacros.h"
#include "Data/Rendering/Headers/VertexBaseData.h"

namespace Data {
namespace Rendering {
  // holds the information about the mesh of a 3D object
  ASSET(AnimatedMeshData,
    (std::vector<AnimatedVertexDataBase>) vertices,
    (uint) vertexCount
  );
  /*
  Currently, by storing the data as an array of AnimatedVertexDataBase's we inflate the size of the data when stored (due to duplicates).
  Leaving it as-is for now to get things working, but will need to update at a later date (maybe a custom deserializer)
  */
}// namespace Rendering

  ASSET_TYPE(Rendering::AnimatedMeshData, "Resources/Meshes/", ".msh");
}// namespace Data