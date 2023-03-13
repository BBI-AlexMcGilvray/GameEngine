#pragma once

#include "Core/IdTypes/InstanceId.h"
#include "Core/Math/Headers/Color.h"

#include "Pipeline/Rendering/Headers/Camera.h"
#include "Pipeline/Rendering/Renderer.h"
#include "Pipeline/Rendering/Shaders/ShaderManager.h"

namespace Application {
namespace Rendering {
  struct RenderManager;

  class IDisplayLayer
  {
    public:
        IDisplayLayer(RenderManager& renderManager)
        : _renderManager(&renderManager)
        {}

        void SetClearColor(const Core::Math::Color& color);

        virtual void Render(Renderer& renderer) = 0;

    protected:
        Core::Math::Color _clearColor;

        RenderManager& _GetRenderManager();

    private:
        Core::Ptr<RenderManager> _renderManager = nullptr;
  };

  class MainDisplayLayer : public IDisplayLayer
  {
    public:
        // if the render manager holds the shader manager, this class doesn't need to hold the shader manager
        MainDisplayLayer(RenderManager& renderManager, ShaderManager& shaderManager, Core::instanceId<Camera> cameraToRender);

        virtual void Render(Renderer& renderer) override;

    private:
        ShaderManager& _shaderManager;
        Core::instanceId<Camera> _cameraToRender;
  };
} // namespace Application
} // namespace Rendering