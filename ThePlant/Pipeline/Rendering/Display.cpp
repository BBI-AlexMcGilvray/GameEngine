#include "Pipeline/Rendering/Display.h"

#include "Pipeline/Rendering/Headers/RenderManager.h"

namespace Application {
namespace Rendering {    
    void IDisplayLayer::SetClearColor(const Core::Math::Color& color)
    {
        _clearColor = color;
    }

    RenderManager& IDisplayLayer::_GetRenderManager() { return *_renderManager; }

    MainDisplayLayer::MainDisplayLayer(RenderManager& renderManager, ShaderManager& shaderManager, Core::instanceId<Camera> cameraToRender)
    : IDisplayLayer(renderManager)
    , _shaderManager(shaderManager)
    , _cameraToRender(cameraToRender)
    {}

    void MainDisplayLayer::Render(Renderer& renderer)
    {
        const RenderCamera& renderCamera = _GetRenderManager().GetCameraManager().GetCamera(_cameraToRender);

        renderer.SetShader(_shaderManager.GetDefaultTextureShader());
        renderCamera.texture.mesh.buffer.Bind();
        renderCamera.texture.actualTexture.Bind();

        // clearing here breaks, that probably means the texture we're trying to render from isn't working?
        glDisable(GL_DEPTH_TEST);
        glClearColor(_clearColor.R, _clearColor.G, _clearColor.B, _clearColor.A);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        glDrawArrays(GL_TRIANGLES, 0, GLsizei(renderCamera.texture.mesh.vertices));

        renderCamera.texture.mesh.buffer.Unbind();
        renderCamera.texture.actualTexture.Unbind();
        renderer.SetShader(Shader());
    }
} // namespace Application
} // namespace Rendering