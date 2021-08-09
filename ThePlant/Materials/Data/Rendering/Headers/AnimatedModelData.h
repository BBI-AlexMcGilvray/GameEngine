#pragma once

#include "Data/Headers/AssetMacros.h"

namespace Data {
namespace Rendering {
  struct AnimatedMeshData;
  struct MaterialData;
  struct SkeletonData;
  struct TextureData;
  
  // holds the information about the mesh of a 3D object
  ASSET(AnimatedModelData,
    (AssetName<MaterialData>) material,
    (AssetName<AnimatedMeshData>) mesh,
    (AssetName<SkeletonData>) skeleton,
    (AssetName<TextureData>) texture
  );
}// namespace Rendering

  ASSET_TYPE(Rendering::AnimatedModelData, "Resources/Models/", ".mdl");
}// namespace Data