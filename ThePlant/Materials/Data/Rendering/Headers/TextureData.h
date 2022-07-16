#pragma once

#include <string>

#include "Core/Math/Headers/Vector2.h"
#include "Core/Headers/BitmaskEnum.h"
#include "Core/Reflection/Enums.h"

#include "Data/Headers/AssetMacros.h"

namespace Data {
namespace Rendering {
  STRING_CAST_ENUM(TextureFlag, int,
    (Invert)(= 1 << 0),
    (UseAlpha)(= 1 << 1)
  );

  STRING_CAST_ENUM(TextureBlendType, int,
    (Multiplicative)(= 1),
    (Additive)(= 2)
  );

  STRING_CAST_ENUM(TextureMapMode, int,
    (Wrap)(= 0),
    (Clamp)(= 1),
    (Decal)(= 2),
    (Mirror)(= 3)
  );

  STRING_CAST_ENUM(TextureType, int,
    (Unknown)(= 0),
    (Diffuse)(= 1),
    (Specular)(= 2),
    (Ambient)(= 3),
    (Emissive)(= 4),
    (HeightMap)(= 5),
    (Normal)(= 6),
    (Shininess)(= 7),
    (Opacity)(= 8),
    (Displaecment)(= 9),
    (Lightmap)(= 10)
  );

  ASSET(TextureData,
    (Core::Math::Float2) size,
    (std::string) imageFile,
    (BitmaskEnum<TextureFlag>) flags,
    (TextureBlendType) blendType,
    (TextureMapMode) mapMode,
    (TextureType) type
  );
}// namespace Rendering

ASSET_TYPE(Rendering::TextureData, "Resources/Textures/", ".txt");
}// namespace Data