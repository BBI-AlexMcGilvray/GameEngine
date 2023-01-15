#pragma once

#include "Pipeline/Rendering/RenderLayer.h"

namespace Application {
namespace Rendering {

class DebugRenderLayer : public RenderLayer<DebugRenderLayer>
{
public:
    void Reset(const Core::Math::Color& clearColor) const;
    void RenderContexts(Renderer& renderer, const RenderCamera& camera) const;
    void RenderSkinnedContexts(Renderer& renderer, const RenderCamera& camera) const;
};

class DefaultRenderLayer : public RenderLayer<DefaultRenderLayer>
{
public:
    void Reset(const Core::Math::Color& clearColor) const;
    void RenderContexts(Renderer& renderer, const RenderCamera& camera) const;
    void RenderSkinnedContexts(Renderer& renderer, const RenderCamera& camera) const;
};

} // namespace Rendering
} // namespace Application