#pragma once

#include <string>
#include <vector>

#include "Core/Headers/TimeDefs.h"
#include "Core/Math/Headers/Quaternion.h"
#include "Core/Math/Headers/Vector3.h"
#include "Core/Reflection/Enums.h"

#include "Data/Headers/AssetMacros.h"

namespace Data {
namespace Rendering {
  // ideally this is nested in the Data::Rendering namespace
  /*
  It can't be nested because the macro defines a specialization of a templated class, and specializations must be defined within the containing namespace
  ** We should probably change the enum to make a struct containing the data of the enum and pass that to the templated function used elsewhere (in meta) instead
      of specializing the template outside of the namespace (since that isn't allowed)
  */
  STRING_CAST_ENUM(AnimationBehaviour, int,
    (Default)(= 0),
    (Constant)(= 1),
    (Linear)(= 2),
    (Repeat)(= 3),
    (Unknown)(= 4)
  );

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