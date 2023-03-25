#include "Pipeline/Rendering/Headers/RenderCamera.h"

#include "Core/Logging/LogFunctions.h"

namespace Application {
namespace Rendering {
RenderCamera::RenderCamera(const Core::instanceId<Camera>& cameraId, const Core::Math::Float4x4& matrix, RenderDataHandle&& renderTargetHandle)
: cameraId(cameraId)
, renderMatrix(matrix)
, renderTargetHandle(std::move(renderTargetHandle))
{
    // _layers = camera.GetLayers(); // should come from the component, not the camera itself
}
}// namespace Rendering
}// namespace Application