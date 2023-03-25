#include "Pipeline/Rendering/Headers/RenderTarget.h"

#include "Core/Logging/LogFunctions.h"

namespace Application {
namespace Rendering {
void InitializeRenderTarget(RenderTarget& renderTarget)
{
    // We should have 'CreateRenderBuffer' and 'CreateTexture' calls (like we do for 'CreateMesh')
    renderTarget.frameBuffer.Generate();
    renderTarget.frameBuffer.Bind();

    // need some way to get the camera buffer size/dimensions
    renderTarget.texture = CreateTexture(renderTarget.renderDimensions, Core::Math::Float2(2.0f, 2.0f));
    if (renderTarget.texture.actualTexture.Object == 0)
    {
        DEBUG_LOG("GLMappedBuffer", "Failed to create texture, glError: " + glGetError());
    }

    renderTarget.texture.actualTexture.Bind(); // may not be needed
    renderTarget.texture.actualTexture.AttachToFrameBuffer(GL_COLOR_ATTACHMENT0);
    renderTarget.texture.actualTexture.Unbind(); // may not be needed

    renderTarget.frameBufferStencilAndDepth.Generate();
    renderTarget.frameBufferStencilAndDepth.Bind();
    renderTarget.frameBufferStencilAndDepth.CreateBufferStorage(renderTarget.renderDimensions, GL_DEPTH24_STENCIL8);
    renderTarget.frameBufferStencilAndDepth.AttachToFrameBuffer(GL_DEPTH_STENCIL_ATTACHMENT);
    renderTarget.frameBufferStencilAndDepth.Unbind();
    
    renderTarget.frameBuffer.Unbind();
}

void DeleteRenderTarget(RenderTarget& renderTarget)
{
    renderTarget.frameBuffer.Delete();
    DeleteTexture(renderTarget.texture);
    renderTarget.frameBufferStencilAndDepth.Delete();
}
}// namespace Rendering
}// namespace Application