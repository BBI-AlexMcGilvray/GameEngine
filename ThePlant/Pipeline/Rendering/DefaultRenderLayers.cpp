#include "Pipeline/Rendering/DefaultRenderLayers.h"

namespace Application {
namespace Rendering {

void DebugRenderLayer::Reset(const Core::Math::Color& clearColor) const
{
  // nothing?
}

void DebugRenderLayer::RenderContexts(Renderer& renderer, const RenderCamera& camera) const
{
    for (auto context : _contexts)
    {
      context.mvp = camera.renderMatrix * context.mvp;
      renderer.SetShader(context.material.shader);
      renderer.DrawMesh(context);
    }
}

void DebugRenderLayer::RenderSkinnedContexts(Renderer& renderer, const RenderCamera& camera) const
{
    for (auto context : _skinnedContexts)
    {
      context.context.mvp = camera.renderMatrix * context.context.mvp;
      renderer.SetShader(context.context.material.shader);
      renderer.DrawMesh(context);
    }
}

void DefaultRenderLayer::Reset(const Core::Math::Color& clearColor) const
{
  // nothing?
}

void DefaultRenderLayer::RenderContexts(Renderer& renderer, const RenderCamera& camera) const
{
    for (auto context : _contexts)
    {
      context.mvp = camera.renderMatrix * context.mvp;
      renderer.SetShader(context.material.shader);
      renderer.DrawMesh(context);
    }
}

void DefaultRenderLayer::RenderSkinnedContexts(Renderer& renderer, const RenderCamera& camera) const
{
    for (auto context : _skinnedContexts)
    {
      context.context.mvp = camera.renderMatrix * context.context.mvp;
      renderer.SetShader(context.context.material.shader);
      renderer.DrawMesh(context);
    }
}

} // namespace Rendering
} // namespace Application