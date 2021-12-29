#pragma once

#include "Data/Headers/AssetManager.h"
#include "Data/Rendering/Headers/SkeletonAnimationData.h"

#include "Pipeline/Animation/Headers/Animation.h"

namespace Application {
namespace Animation {
  Animation CreateAnimation(Data::AssetManager& assetManager, const Data::AssetName<Data::Rendering::SkeletonAnimationData>& asset);
}// namespace Animation
}// namespace Application