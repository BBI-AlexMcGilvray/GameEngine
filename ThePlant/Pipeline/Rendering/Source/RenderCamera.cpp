#include "Pipeline/Rendering/Headers/RenderCamera.h"

namespace Application {
namespace Rendering {
RenderCamera::RenderCamera(const Camera& camera, const Core::Math::Int2& renderDimensions, const Core::Math::Float4x4& matrix)
: renderMatrix(matrix)
, renderDimensions(renderDimensions)
{
    cameraId = camera.GetCameraId();
    _InitializeBuffers();
    // _layers = camera.GetLayers();
}

RenderCamera::~RenderCamera()
{
    _CleanUpBuffers();// should this be here?
}

void RenderCamera::_InitializeBuffers()
{
    frameBuffer.Generate();
    frameBuffer.Bind();

    // need some way to get the camera buffer size/dimensions
    texture = CreateTexture(renderDimensions, Core::Math::Float2(2.0f, 2.0f));
    texture.actualTexture.AttachToFrameBuffer(GL_COLOR_ATTACHMENT0);

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