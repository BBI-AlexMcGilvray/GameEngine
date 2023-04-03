#pragma once

#include "Core/Math/Headers/Vector2.h"

#include "Pipeline/Rendering/2D/Headers/Texture.h"
#include "Pipeline/Rendering/MeshManager.h"
#include "Pipeline/Rendering/Headers/RenderData.h"
#include "Pipeline/Rendering/OpenGL/Headers/GLFrameBuffer.h"
#include "Pipeline/Rendering/OpenGL/Headers/GLRenderBuffer.h"

namespace Application {
namespace Rendering {
  /*
  Doesn't really make sense for RenderTargets to have a manager (effectively camera manager really...)
  since they only are used on render thread anyways
  */
  struct RenderTarget : public TRenderData<RenderTarget>
  {
    Core::Math::Int2 renderDimensions;
    GLFrameBuffer frameBuffer;
    GLRenderBuffer frameBufferStencilAndDepth;
    Texture texture;

    RenderTarget() = default;
    RenderTarget(const Core::Math::Int2& renderDimensions)
    : renderDimensions(renderDimensions)
    {}
  };

  void InitializeRenderTarget(RenderTarget& renderTarget, MeshManager& meshManager);
  void DeleteRenderTarget(RenderTarget& renderTarget);
}// namespace Rendering
}// namespace Application