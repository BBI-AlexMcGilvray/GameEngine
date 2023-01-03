#include "Pipeline/Rendering/RenderFrame.h"

#include "Core/Debugging/Memory/MemoryTrackerUtils.h"
#include "Core/Debugging/Profiling/Utils.h"

#include <algorithm>
#include <set>

namespace Application {
namespace Rendering {
void RenderFrame::QueueCamera(const RenderCamera& camera)
{
    _cameras.push_back(camera);
    SetMainCamera(camera.cameraId); // this should be explicitly called elsewhere
}

void RenderFrame::MoveTo(RenderFrame& moveTo) const
{
    SCOPED_MEMORY_CATEGORY("Rendering");
    moveTo._cameras = std::move(_cameras);
    moveTo._mainCamera = _mainCamera;
    moveTo._dirtyLayers = _dirtyLayers;
    for (const auto& layer : _layers)
    {
        // don't move the layers list as we want to keep the layers we added previously
        moveTo._layers.push_back(layer->CopyAndMoveTo());
    }
}

void RenderFrame::SetMainCamera(const Core::instanceId<Camera>& camera)
{
    _mainCamera = camera;
}

void RenderFrame::Render(Renderer& renderer) const
{
    DEBUG_PROFILE_SCOPE("RenderFrame::Render");
    
    // NOTES:
    /*
      - if we want shaders to get a delta time, we can provide that here by adding a field to the contexts (and providing a delta time)
      - by not using 'const auto&' we are making a copy, we need to do this at the moment to include the camera matrix
        - maybe the 'DrawMesh' call should just take in a camera matrix as well
    */

    // need to make sure the layers are ordered before the below code

    // rendering to cameras should happen as a separate stage to using the camera's texture (after everything is rendered, the results are then handled by 'display'(?) logic)

    for (auto& camera : _cameras)
    {
        camera.BeginCameraRender(Core::Math::PINK * 0.25f);
        // activate the camera's own 'layer' (frame buffer)
        for (auto& layer : _layers)
        {
            // if layer applies to camera
            layer->Render(renderer, camera.renderMatrix);
        }
        camera.EndCameraRender();
    }
}

const RenderCamera& RenderFrame::GetMainCamera() const
{
    for (auto& camera : _cameras)
    {
        if (camera.cameraId == _mainCamera)
        {
            return camera;
        }
    }

    CORE_THROW("RenderFrame", "Main camera does not exist");
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
    SCOPED_MEMORY_CATEGORY("Rendering");

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
    SCOPED_MEMORY_CATEGORY("Rendering");

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
    if (!_IsDirty())
    {
        return;
    }

    SCOPED_MEMORY_CATEGORY("ECS");
    std::vector<Core::UniquePtr<IRenderLayer>> sortedLayers;
    
    auto dependenciesSorted = [&sortedLayers, this](const std::vector<Core::runtimeId_t>& dependencies)
    {
        for (const auto& dependency : dependencies)
        {
            auto inLayers = std::find_if(_layers.begin(), _layers.end(), [&dependency](const auto& layer)
            {
                return layer->IsLayer(dependency);
            });
            // if the system is not loaded, the dependency is fulfilled (maybe not the most safe...)
            if (inLayers == _layers.end())
            {
                return true;
            }

            auto& inSorted = std::find_if(sortedLayers.begin(), sortedLayers.end(), [&dependency](const auto& layer)
            {
                return layer->IsLayer(dependency);
            });

            if (inSorted == sortedLayers.end())
            {
                return false;
            }
        }

        return true;
    };

    while (_layers.size() > 0)
    {
        for (auto& iter = _layers.begin(); iter != _layers.end();/* handled in-loop */)
        {
            const std::vector<Core::runtimeId_t>& dependencies = (*iter)->GetDependencies();
            if (dependencies.size() == 0 || dependenciesSorted(dependencies))
            {
                sortedLayers.emplace_back(std::move(*iter));
                iter = _layers.erase(iter);
            }
            else
            {
                ++iter;
            }
        }
    }

    DEBUG_ASSERT(_layers.size() == 0);
    _layers = std::move(sortedLayers);

    _Clean();
}
}// namespace Rendering
}// namespace Application