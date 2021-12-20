#pragma once

#include "Data/Headers/AssetData.h"
#include "Data/Rendering/Headers/SkeletonData.h"

#include "Pipeline/ECSSystems/RenderingComponents.h"

namespace Application {
namespace Rendering {
  SkeletonComponent CreateSkeleton(const Data::AssetData<Data::Rendering::SkeletonData>& skeleton, const EntityId& parent);
}// namespace Rendering
}// namespace Application