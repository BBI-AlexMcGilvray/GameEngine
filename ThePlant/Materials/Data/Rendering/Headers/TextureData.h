#pragma once

#include <string>

#include "Core/Math/Headers/Vector2.h"

#include "Data/Headers/AssetMacros.h"

namespace Data {
namespace Rendering {
  ASSET(TextureData,
    (Core::Math::Float2) size,
    (std::string) imageFile
  );
}// namespace Rendering

ASSET_TYPE(Rendering::TextureData, "Resources/Textures/", ".txt");
}// namespace Data