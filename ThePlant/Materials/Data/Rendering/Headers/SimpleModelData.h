#pragma once

#include "Data/Headers/AssetMacros.h"

namespace Data {
namespace Rendering {
  struct MaterialData;
  struct SimpleMeshData;
  struct TextureData;

  // holds the information about the mesh of a 3D object
  ASSET(SimpleModelData,
    (AssetName<MaterialData>) material,
    (AssetName<SimpleMeshData>) mesh,
    (AssetName<TextureData>) texture
  );
}// namespace Rendering

ASSET_TYPE(Rendering::SimpleModelData, "Resource/Models/", ".mdl");
}// namespace Data