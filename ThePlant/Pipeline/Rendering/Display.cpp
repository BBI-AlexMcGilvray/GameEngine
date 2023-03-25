#include "Pipeline/Rendering/Display.h"

#include "Pipeline/Rendering/Headers/RenderManager.h"

namespace Application {
namespace Rendering {    
    void IDisplayLayer::SetClearColor(const Core::Math::Color& color)
    {
        _clearColor = color;
    }

    MainDisplayLayer::MainDisplayLayer(RenderManager& renderManager, ShaderManager& shaderManager, Core::instanceId<Camera> cameraToRender)
    : _renderManager(renderManager)
    , _shaderManager(shaderManager)
    , _cameraToRender(cameraToRender)
    {}

    void MainDisplayLayer::Render(Renderer& renderer)
    {
        auto& cameraManager = _renderManager.GetCameraManager();
        const auto& renderTexture = cameraManager.GetValidRenderTarget(cameraManager.GetCamera(_cameraToRender).renderTargetHandle);

        renderer.SetShader(_shaderManager.GetDefaultTextureShaderHandle());
        renderTexture.texture.mesh.buffer.Bind();
        renderTexture.texture.actualTexture.Bind();

        // clearing here breaks, that probably means the texture we're trying to render from isn't working?
        glDisable(GL_DEPTH_TEST);
        glClearColor(_clearColor.R, _clearColor.G, _clearColor.B, _clearColor.A);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        glDrawArrays(GL_TRIANGLES, 0, GLsizei(renderTexture.texture.mesh.vertices));

        renderTexture.texture.mesh.buffer.Unbind();
        renderTexture.texture.actualTexture.Unbind();
        renderer.ClearShader();
    }
} // namespace Application
} // namespace Rendering