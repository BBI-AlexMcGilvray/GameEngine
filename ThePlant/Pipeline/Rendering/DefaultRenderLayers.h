#pragma once

#include "Pipeline/Rendering/RenderLayer.h"

namespace Application {
namespace Rendering {

class DebugRenderLayer : public RenderLayer<DebugRenderLayer>
{
public:
    void RenderContexts(Renderer& renderer, const Core::Math::Float4x4& camera) const;
    void RenderSkinnedContexts(Renderer& renderer, const Core::Math::Float4x4& camera) const;
};

class DefaultRenderLayer : public RenderLayer<DefaultRenderLayer>
{
public:
    void RenderContexts(Renderer& renderer, const Core::Math::Float4x4& camera) const;
    void RenderSkinnedContexts(Renderer& renderer, const Core::Math::Float4x4& camera) const;
};

} // namespace Rendering
} // namespace Application