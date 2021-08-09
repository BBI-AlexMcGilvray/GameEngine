#pragma once

#include <string>
#include <vector>

#include "Core/Math/Headers/Vector2.h"
#include "Core/Math/Headers/Vector3.h"
#include "Core/Math/Headers/Vector4.h"

#include "Data/Headers/AssetMacros.h"

namespace Data {
namespace Rendering {
  ASSET(SimpleVertexDataBase,
    (Core::Math::Float3) position,
    (Core::Math::Float3) normal
  );

  ASSET(VertexDataBase,
    (Core::Math::Float3) position,
    (Core::Math::Float3) normal,
    (Core::Math::Float2) uvs
  );

  ASSET(AnimatedVertexDataBase,
    (Core::Math::Float3) position,
    (Core::Math::Float3) normal,
    (Core::Math::Float2) uvs,
    (std::vector<std::string>) boneName,
    (Core::Math::Float4) boneWeight
  );
}// namespace Rendering
}// namespace Data