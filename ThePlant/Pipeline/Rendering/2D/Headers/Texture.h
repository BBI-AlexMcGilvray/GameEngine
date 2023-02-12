#pragma once

#include "Core/Math/Headers/Vector2.h"

#include "Pipeline/Rendering/OpenGL/Headers/GLTexture.h"
#include "Pipeline/Rendering/2D/Headers/SimpleShapes.h"

namespace Application {
namespace Rendering {
  // holds an image that gets used, and a type of material
  struct Texture
  {
    Core::Math::Int2 textureDimensions;
    GLTexture actualTexture; // this texture should be a GLTexture with 'our' data (i.e. size)
    Mesh mesh; // shouldn't be here - this should be a sprite or an image (do we need both?)
  };

  Texture CreateTexture(const Core::Math::Int2& textureDimensions, const Core::Math::Float2& meshDimensions);
  void DeleteTexture(Texture& texture);

  void ResizeTexture(Texture& texture, const Core::Math::Int2& newDimensions);
  void ResizeMesh(Texture& texture, const Core::Math::Float2& newDimensions);
}// namespace Rendering
}// namespace Application