#pragma once

#include <string>
#include <vector>

#include "Core/Headers/TimeDefs.h"
#include "Core/Math/Headers/Quaternion.h"
#include "Core/Math/Headers/Vector3.h"

#include "Data/Headers/AssetMacros.h"
#include "Data/Headers/SerializationUtils.h"

namespace Data {
namespace Rendering {
  NESTED_ASSET(PositionFrameData,
    (Core::Math::Float3) position,
    (Core::Second) time
  );

  NESTED_ASSET(RotationFrameData,
    (Core::Math::FQuaternion) rotation,
    (Core::Second) time
  );

  NESTED_ASSET(ScaleFrameData,
    (Core::Math::Float3) scale,
    (Core::Second) time
  );

  enum class AnimationBehaviour {
    Default,
    Constant,
    Linear,
    Repeat,
    Unknown
  };

  NESTED_ASSET(BoneAnimationData,
    (std::string) name,
    (AnimationBehaviour) preBehaviour,
    (AnimationBehaviour) postBehaviour,
    (std::vector<PositionFrameData>) positionChannel,
    (std::vector<RotationFrameData>) rotationChannel,
    (std::vector<ScaleFrameData>) scaleChannel
  );

  ASSET(SkeletonAnimationData,
    (std::string) name,
    (std::vector<BoneAnimationData>) boneAnimations,
    (Core::Second) duration
  );
}// namespace Rendering

ASSET_TYPE(Rendering::SkeletonAnimationData, "Resources/SkeletonAnimations/", ".sanim");
}// namespace Data