#pragma once

#include <array>

#include "Core/Headers/CoreDefs.h"
#include "Core/Math/Headers/Color.h"
#include "Core/Math/Headers/Matrix4x4.h"

#include "Pipeline/Rendering/RenderContext.h"
#include "Pipeline/Rendering/Shaders/Shader.h"

namespace Application {
namespace Rendering {

  // handles the actual rendering of any and all objects (probably should specialize for 2D and 3D objects)
  // this should also hold (a point perhaps) to the camera that is being used by the system
  struct Renderer
  {
    void StartFrame();
    void EndFrame();

    // must be called before any meshes that need that shader (or once per set)
    void SetShader(const Shader& shader);
    // should contain the logic that is currently in the shader and the render object
    void DrawMesh(const Context& context) const;
    void DrawMesh(const SkinnedContext& context) const;

  private:
  #ifdef DEBUG
    struct TrackingInfo
    {
      uint shadersUsed = 0;
      uint drawCalls = 0;
      uint modelsDrawn = 0;
      uint skinnedModelsDrawn = 0;
    };
    mutable TrackingInfo _trackingInfo; // ideally this is actually thread-safe, but since it is just debugging for now it doesn't matter too much

    void _ResetTrackingInfo() const;
    void _PrintTrackingInfo() const;
  #endif

    Shader _currentShader; // used for tracking shader changes and ordering information
    // Renderer<OpenGL> _impl; // when we support multiple renderers, we would want to swap the impl at compile type (or launch time based on GPU?) and have the 'final' calls as part of that renderer

    // is this needed?
    void _Draw(const Context& context) const;

    void _DrawLines(Core::size vertexCount) const;
    void _DrawTriangles(Core::size vertexCount) const;

    void _SetShaderVariables(const Context& context) const;
    void _SetShaderVariables(const SkinnedContext& context) const;
    void _SetMaterialContext(const Material& material) const;
  };
}// namespace Rendering
}// namespace Application