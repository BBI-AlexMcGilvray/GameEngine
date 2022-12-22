#include "Pipeline/Rendering/RenderFrame.h"

#include "Core/Debugging/Memory/MemoryTrackerUtils.h"
#include "Core/Debugging/Profiling/Utils.h"

namespace Application {
namespace Rendering {
void RenderFrame::QueueCamera(const Core::Math::Float4x4& camera)
{
    _cameras.push_back(camera);
}

void RenderFrame::Render(Renderer& renderer) const
{
    DEBUG_PROFILE_SCOPE("_RenderFrameForCamera");
    
    // NOTES:
    /*
      - if we want shaders to get a delta time, we can provide that here by adding a field to the contexts (and providing a delta time)
      - by not using 'const auto&' we are making a copy, we need to do this at the moment to include the camera matrix
        - maybe the 'DrawMesh' call should just take in a camera matrix as well
    */

    // need to make sure the layers are ordered before the below code

    for (auto& camera : _cameras)
    {
        for (auto& layer : _layers)
        {
            layer->Render(renderer, camera);
        }
    }
}

void RenderFrame::Clear()
{
    _cameras.clear();
    for (auto& layer : _layers)
    {
        layer->Clear();
    }
}

void RenderFrame::_QueueRender(const Context& context, const Core::runtimeId_t& targetLayer)
{
    for (auto& layer : _layers)
    {
        if (layer->IsLayer(targetLayer))
        {
            layer->QueueRender(context);
            return;
        }
    }
}

void RenderFrame::_QueueRender(const SkinnedContext& context, const Core::runtimeId_t& targetLayer)
{
    for (auto& layer : _layers)
    {
        if (layer->IsLayer(targetLayer))
        {
            layer->QueueRender(context);
            return;
        }
    }
}

void RenderFrame::OrderLayers()
{
    if (!_dirtyLayers)
    {
        return;
    }

    // sort layers
    CORE_LOG("RenderFrame", "Need to order the layers!");
    _dirtyLayers = true;
}
}// namespace Rendering
}// namespace Application