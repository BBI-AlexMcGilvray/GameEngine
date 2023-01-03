#pragma once

#include <set>

#include "Core/Headers/Hash.h"
#include "Core/IdTypes/InstanceId.h"
#include "Core/Math/Headers/Matrix4x4.h"
#include "Core/Math/Headers/Vector2.h"
#include "Core/Math/Headers/Color.h"

#include "Pipeline/Rendering/Headers/Camera.h"
#include "Pipeline/Rendering/2D/Headers/Texture.h"
#include "Pipeline/Rendering/OpenGL/Headers/GLFrameBuffer.h"
#include "Pipeline/Rendering/OpenGL/Headers/GLRenderBuffer.h"

namespace Application {
namespace Rendering {
  // anything needed for camera. should create specifications for perspective and orthographic
  struct RenderCamera
  {
    Core::instanceId<Camera> cameraId;
    Core::Math::Int2 renderDimensions;
    Core::Math::Float4x4 renderMatrix;
    GLFrameBuffer frameBuffer;
    Texture texture; // this should probably be an actual 'Texture'
    // we will have this when it is able to be supported (i.e. set properly)
    std::set<Core::Hash> layers;

    RenderCamera(const Camera& camera, const Core::Math::Int2& renderDimensions, const Core::Math::Float4x4& matrix);
    ~RenderCamera();

    // coping should be fine, just need to be aware of where the frame buffers will get deleted from (could be race condition in multithreaded rendering)
    RenderCamera(const RenderCamera&) = default;
    RenderCamera(RenderCamera&&) = default;

    RenderCamera& operator=(const RenderCamera&) = default;
    RenderCamera& operator=(RenderCamera&&) = default;

    void BeginCameraRender(const Core::Math::Color& clearColour) const;
    void EndCameraRender() const;

private:
    GLRenderBuffer _frameBufferStencilAndDepth;

    void _InitializeBuffers();
    void _CleanUpBuffers();
  };
}// namespace Rendering
}// namespace Application