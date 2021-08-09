#pragma once

#include "Core/Math/Headers/Color.h"
#include "Data/Headers/AssetMacros.h"

namespace Data {
namespace Rendering {
  ASSET(MaterialData,
    (Core::Math::Color) specular,
    (Core::Math::Color) diffuse,
    (Core::Math::Color) ambient,
    (float) shininess
  );
}// namespace Rendering

ASSET_TYPE(Rendering::MaterialData, "Resources/Materials/", ".mat");
}// namespace Data