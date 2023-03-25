#pragma once

#include <set>

#include "Core/Headers/Hash.h"
#include "Core/IdTypes/InstanceId.h"
#include "Core/Math/Headers/Matrix4x4.h"
#include "Core/Math/Headers/Vector2.h"
#include "Core/Math/Headers/Color.h"

#include "Pipeline/Rendering/Headers/Camera.h"
#include "Pipeline/Rendering/2D/Headers/Texture.h"
#include "Pipeline/Rendering/Headers/RenderTarget.h"
#include "Pipeline/Rendering/OpenGL/Headers/GLFrameBuffer.h"
#include "Pipeline/Rendering/OpenGL/Headers/GLRenderBuffer.h"

namespace Application {
namespace Rendering {
  // anything needed for camera. should create specifications for perspective and orthographic
  struct RenderCamera
  {
    Core::instanceId<Camera> cameraId;
    Core::Math::Float4x4 renderMatrix;
    // we will have this when it is able to be supported (i.e. set properly)
    std::set<Core::Hash> layers;

    RenderDataHandle renderTargetHandle;

    RenderCamera(const Core::instanceId<Camera>& cameraId, const Core::Math::Float4x4& matrix, RenderDataHandle&& renderTargetHandle);
    ~RenderCamera() noexcept = default;

    // copying should be fine, just need to be aware of where the frame buffers will get deleted from (could be race condition in multithreaded rendering)
    RenderCamera(RenderCamera&&) = default;
    RenderCamera& operator=(RenderCamera&&) = default;

    RenderCamera(const RenderCamera&) = default;
    RenderCamera& operator=(const RenderCamera&) = default;
  };
}// namespace Rendering
}// namespace Application