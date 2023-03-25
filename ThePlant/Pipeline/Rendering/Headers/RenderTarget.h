#pragma once

#include "Core/Math/Headers/Vector2.h"

#include "Pipeline/Rendering/2D/Headers/Texture.h"
#include "Pipeline/Rendering/Headers/RenderData.h"
#include "Pipeline/Rendering/OpenGL/Headers/GLFrameBuffer.h"
#include "Pipeline/Rendering/OpenGL/Headers/GLRenderBuffer.h"

namespace Application {
namespace Rendering {
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

  void InitializeRenderTarget(RenderTarget& renderTarget);
  void DeleteRenderTarget(RenderTarget& renderTarget);
}// namespace Rendering
}// namespace Application