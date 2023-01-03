#pragma once

#include <vector>

#include "Core/Logging/LogFunctions.h"

#include "Pipeline/Rendering/Headers/RenderCamera.h"
#include "Pipeline/Rendering/RenderLayer.h"

namespace Application {
namespace Rendering {
    // maybe have this include the camera(s?) to use
    struct RenderFrame
    {
        RenderFrame() = default;
        RenderFrame(RenderFrame&&) = default;
        RenderFrame& operator=(RenderFrame&&) = default;
        ~RenderFrame() = default;

        RenderFrame(const RenderFrame&) = delete;
        RenderFrame& operator=(const RenderFrame&) = delete;

        template <typename LAYER>
        LAYER& AddLayer()
        {
            SCOPED_MEMORY_CATEGORY("Rendering");

            if (auto iter = std::find_if(_layers.begin(), _layers.end(), [](const std::unique_ptr<IRenderLayer>& layer)
            {
                return layer->IsLayer(Core::GetTypeId<LAYER>());
            }); iter != _layers.end())
            {
                DEBUG_THROW("RenderLayer", "Adding layer twice!");
                return static_cast<LAYER&>(*(*iter));
            }
            else
            {
                _layers.push_back(std::make_unique<LAYER>());
                _Dirty();
                return static_cast<LAYER&>(*_layers[_layers.size() - 1]);
            }
        }

        template <typename LAYER>
        void RemoveLayer()
        {
            if (auto iter = std::find(_layers.begin(), _layers.end(), [](const std::unique_ptr<IRenderLayer>& layer)
            {
                return layer->IsLayer(Core::GetTypeId<LAYER>());
            }); iter != _layers.end())
            {
                _layers.erase(iter);
                _Dirty();
            }
            else
            {
                DEBUG_THROW("RenderFrame", "Removing a non-existent layer");
            }            
        }

        void QueueCamera(const RenderCamera& camera);

        template <typename LAYER>
        void QueueRender(const Context& context)
        {
            _QueueRender(context, Core::GetTypeId<LAYER>());
        }
        
        template <typename LAYER>
        void QueueRender(const SkinnedContext& context)
        {
            _QueueRender(context, Core::GetTypeId<LAYER>());
        }

        void OrderLayers(); // can this be moved elsewhere so it is implicitly called? could be done if made const and the layers/bool made mutable
        // we assume moveTo in a fresh state
        void MoveTo(RenderFrame& moveTo) const;

        void SetMainCamera(const Core::instanceId<Camera>& camera);
        void Render(Renderer& renderer) const;
        const RenderCamera& GetMainCamera() const;

        void Clear();

    private:
        // as mentioned in RenderLayer, the cameras here should have a collection of what layers they render
        // that information should be held in the CameraComponent
        std::vector<RenderCamera> _cameras; // can't be references because we move to other render frames (and references could break)
        Core::instanceId<Camera> _mainCamera; // this is the camera that renders to the main window
        bool _dirtyLayers = false;
        std::vector<std::unique_ptr<IRenderLayer>> _layers;

        void _Dirty() { _dirtyLayers = true; }
        void _Clean() { _dirtyLayers = false; }
        bool _IsDirty() const { return _dirtyLayers; }
        
        void _QueueRender(const Context& context, const Core::runtimeId_t& targetLayer);
        void _QueueRender(const SkinnedContext& context, const Core::runtimeId_t& targetLayer);
    };
}// namespace Rendering
}// namespace Application