#pragma once

#include <string>
#include <vector>

#include "Core/Math/Headers/Quaternion.h"
#include "Core/Math/Headers/Vector3.h"

#include "Data/Headers/AssetMacros.h"
#include "Data/Rendering/Headers/SkeletonAnimationData.h"

namespace Data {
namespace Rendering {
  ASSET(SkeletonBoneData,
    (std::string) name,
    (Core::Math::Float3) position,
    (Core::Math::FQuaternion) rotation,
    (Core::Math::Float3) scale,
    (uint) children
  );

  /*
  Skeletons store their bones in one array, with the tree being built by investigating the children each bone has
    - A single 'branch' the of the skeleton 'tree' is completed before going further down the hierarchy
  */

  ASSET(SkeletonData,
    (std::vector<SkeletonBoneData>) bones,
    (std::vector<AssetName<SkeletonAnimationData>>) animations
  );
}// namespace Rendering

ASSET_TYPE(Rendering::SkeletonData, "Resources/Skeletons/", ".skl");
}// namespace Data