#pragma once

#include <vector>

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
        void AddLayer()
        {
        #if DEBUG
            if (std::find(_layers.begin(), _layers.end(), Core::GetTypeId<LAYER>()) != _layers.end())
            {
                CORE_THROW("RenderLayer", "Adding layer twice!");
            }
        #endif
            _layers.push_back(std::make_unique<LAYER>());
            _dirtyLayers = true;
        }

        template <typename LAYER>
        void RemoveLayer()
        {
            if (auto iter = std::find(_layers.begin(), _layers.end(), Core::GetTypeId<LAYER>()))
            {
                _layers.remove(iter);
                _dirtyLayers = true;
            }
        #if DEBUG
            else
            {
                CORE_THROW("RenderFrame", "Removing a non-existent layer");
            }
        #endif            
        }

        void QueueCamera(const Core::Math::Float4x4& camera);

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
        void Render(Renderer& renderer) const;

        void Clear();

    private:
        // as mentioned in RenderLayer, the cameras here should have a collection of what layers they render
        // that information should be held in the CameraComponent
        std::vector<Core::Math::Float4x4> _cameras;
        bool _dirtyLayers = false;
        std::vector<std::unique_ptr<IRenderLayer>> _layers;
        
        void _QueueRender(const Context& context, const Core::runtimeId_t& targetLayer);
        void _QueueRender(const SkinnedContext& context, const Core::runtimeId_t& targetLayer);
    };
}// namespace Rendering
}// namespace Application