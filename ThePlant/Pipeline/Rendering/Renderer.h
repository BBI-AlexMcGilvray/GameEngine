#pragma once

#include <array>

#include "Core/Headers/CoreDefs.h"
#include "Core/Math/Headers/Color.h"
#include "Core/Math/Headers/Matrix4x4.h"

#include "Pipeline/Rendering/RenderContext.h"
#include "Pipeline/Rendering/Headers/CameraManager.h"
#include "Pipeline/Rendering/Headers/RenderTarget.h"
#include "Pipeline/Rendering/Shaders/Shader.h"
#include "Pipeline/Rendering/Shaders/ShaderManager.h"

namespace Application {
namespace Rendering {

  // handles the actual rendering of any and all objects (probably should specialize for 2D and 3D objects)
  // this should also hold (a point perhaps) to the camera that is being used by the system
  struct Renderer
  {
    Renderer(ShaderManager& shaderManager, CameraManager& cameraManager);

    void StartFrame();
    void EndFrame();

    // must be called before any meshes that need that shader (or once per set)
    void SetShader(const RenderDataHandle& shader);
    void ClearShader();

    void SetRenderTarget(const RenderDataHandle& renderTarget, const Core::Math::Color& clearColour);
    void ClearRenderTarget();

    // should contain the logic that is currently in the shader and the render object
    void DrawMesh(const Context& context) const;
    void DrawMesh(const SkinnedContext& context) const;

  private:
  #ifdef DEBUG
    struct TrackingInfo
    {
      uint renderTargetsUsed = 0;
      uint shadersUsed = 0;
      uint drawCalls = 0;
      uint modelsDrawn = 0;
      uint skinnedModelsDrawn = 0;
    };
    mutable TrackingInfo _trackingInfo; // ideally this is actually thread-safe, but since it is just debugging for now it doesn't matter too much

    void _ResetTrackingInfo() const;
    void _PrintTrackingInfo() const;
  #endif

    CameraManager& _cameraManager;
    ShaderManager& _shaderManager;
    // ideally these aren't pointers... but we can't copy render data so they can't be references
    Core::Ptr<const RenderTarget> _currentTarget = nullptr;
    Core::Ptr<const ShaderData> _currentShader = nullptr; // used for tracking shader changes and ordering information
    // Renderer<OpenGL> _impl; // when we support multiple renderers, we would want to swap the impl at compile type (or launch time based on GPU?) and have the 'final' calls as part of that renderer

    // is this needed?
    void _Draw(const Context& context) const;

    void _DrawLines(Core::size vertexCount) const;
    void _DrawTriangles(Core::size vertexCount) const;

#if DEBUG
    void _SetDrawMode(const Context& context) const;
#endif

    void _SetShaderVariables(const Context& context) const;
    void _SetShaderVariables(const SkinnedContext& context) const;
    void _SetMaterialContext(const Material& material) const;
  };
}// namespace Rendering
}// namespace Application