#include "Pipeline/Rendering/Headers/RenderCamera.h"

#include "Core/Logging/LogFunctions.h"

namespace Application {
namespace Rendering {
RenderCamera::RenderCamera(const Camera& camera, const Core::Math::Int2& renderDimensions, const Core::Math::Float4x4& matrix)
: renderMatrix(matrix)
, renderDimensions(renderDimensions)
{
    cameraId = camera.GetCameraId();
    // _layers = camera.GetLayers(); // should come from the component, not the camera itself
}

void RenderCamera::InitializeCamera()
{
    _InitializeBuffers();
}

// in the future, this clear colour should be camera/render camera specific
void RenderCamera::BeginCameraRender(const Core::Math::Color& clearColour) const
{
    frameBuffer.Bind();
    glEnable(GL_DEPTH_TEST);
    glClearColor(clearColour.R, clearColour.G, clearColour.B, clearColour.A);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}

void RenderCamera::EndCameraRender() const
{
    frameBuffer.Unbind();
}

void RenderCamera::CleanUpCamera()
{
    _CleanUpBuffers();
}

// currently commented out from constructor
void RenderCamera::_InitializeBuffers()
{
    // We should have 'CreateRenderBuffer' and 'CreateTexture' calls (like we do for 'CreateMesh')
    frameBuffer.Generate();
    frameBuffer.Bind();

    // need some way to get the camera buffer size/dimensions
    texture = CreateTexture(renderDimensions, Core::Math::Float2(2.0f, 2.0f));
    if (texture.actualTexture.Object == 0)
    {
        DEBUG_LOG("GLMappedBuffer", "Failed to create texture, glError: " + glGetError());
    }

    texture.actualTexture.Bind(); // may not be needed
    texture.actualTexture.AttachToFrameBuffer(GL_COLOR_ATTACHMENT0);
    texture.actualTexture.Unbind(); // may not be needed

    _frameBufferStencilAndDepth.Generate();
    _frameBufferStencilAndDepth.Bind();
    _frameBufferStencilAndDepth.CreateBufferStorage(renderDimensions, GL_DEPTH24_STENCIL8);
    _frameBufferStencilAndDepth.AttachToFrameBuffer(GL_DEPTH_STENCIL_ATTACHMENT);
    _frameBufferStencilAndDepth.Unbind();
    
    frameBuffer.Unbind();

    // the shader will need to be set up elsewhere
}

void RenderCamera::_CleanUpBuffers()
{
    frameBuffer.Delete();
    DeleteTexture(texture);
    _frameBufferStencilAndDepth.Delete();
}
}// namespace Rendering
}// namespace Application