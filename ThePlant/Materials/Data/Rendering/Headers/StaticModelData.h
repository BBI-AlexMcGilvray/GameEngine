#pragma once

#include "Data/Headers/AssetMacros.h"

namespace Data {
namespace Rendering {
  struct MaterialData;
  struct StaticMeshData;
  struct TextureData;

  // holds the information about the mesh of a 3D object
  ASSET(StaticModelData,
    (AssetName<MaterialData>) material,
    (AssetName<StaticMeshData>) mesh,
    (AssetName<TextureData>) texture
  );
}// namespace Rendering

ASSET_TYPE(Rendering::StaticModelData, "Resources/Models/", ".mdl");
}// namespace Data