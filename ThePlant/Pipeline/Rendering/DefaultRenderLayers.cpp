#include "Pipeline/Rendering/DefaultRenderLayers.h"

namespace Application {
namespace Rendering {

void DebugRenderLayer::RenderContexts(Renderer& renderer, const Core::Math::Float4x4& camera) const
{
    for (auto context : _contexts)
    {
      context.mvp = camera * context.mvp;
      renderer.SetShader(context.material.shader);
      renderer.DrawMesh(context);
    }
}

void DebugRenderLayer::RenderSkinnedContexts(Renderer& renderer, const Core::Math::Float4x4& camera) const
{
    for (auto context : _skinnedContexts)
    {
      context.context.mvp = camera * context.context.mvp;
      renderer.SetShader(context.context.material.shader);
      renderer.DrawMesh(context);
    }
}

void DefaultRenderLayer::RenderContexts(Renderer& renderer, const Core::Math::Float4x4& camera) const
{
    for (auto context : _contexts)
    {
      context.mvp = camera * context.mvp;
      renderer.SetShader(context.material.shader);
      renderer.DrawMesh(context);
    }
}

void DefaultRenderLayer::RenderSkinnedContexts(Renderer& renderer, const Core::Math::Float4x4& camera) const
{
    for (auto context : _skinnedContexts)
    {
      context.context.mvp = camera * context.context.mvp;
      renderer.SetShader(context.context.material.shader);
      renderer.DrawMesh(context);
    }
}

} // namespace Rendering
} // namespace Application