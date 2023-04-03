#pragma once

#include "Core/Math/Headers/Vector2.h"

#include "Pipeline/Rendering/OpenGL/Headers/GLTexture.h"
#include "Pipeline/Rendering/2D/Headers/SimpleShapes.h"
#include "Pipeline/Rendering/MeshManager.h"

namespace Application {
namespace Rendering {
  // holds an image that gets used, and a type of material (material should be indexed into the material manager)
  // these should probably be held by a general texture manager (indexed by an instance id) so that they can be shared and loaded at one time
  struct Texture
  {
    Core::Math::Int2 textureDimensions;
    GLTexture actualTexture; // this texture should be a GLTexture with 'our' data (i.e. size)
    RenderDataHandle mesh; // shouldn't be here - this should be a sprite or an image (do we need both?)
  };

  // not sure how creating a texture in a space where opengl is being run on a separate thread will work...
  Texture CreateTexture(MeshManager& meshManager, const Core::Math::Int2& textureDimensions, const Core::Math::Float2& meshDimensions);
  void DeleteTexture(Texture& texture);

  void ResizeTexture(Texture& texture, const Core::Math::Int2& newDimensions);
  void ResizeMesh(MeshManager& meshManager, Texture& texture, const Core::Math::Float2& newDimensions);
}// namespace Rendering
}// namespace Application