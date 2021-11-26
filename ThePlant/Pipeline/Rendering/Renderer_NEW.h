#pragma once

#include <array>

#include "Core/Headers/CoreDefs.h"
#include "Core/Math/Headers/Color.h"
#include "Core/Math/Headers/Matrix4x4.h"

#include "Pipeline/Rendering/RenderContext.h"
#include "Pipeline/Rendering/Shaders/Shader_NEW.h"

namespace Application {
namespace Rendering {

  // handles the actual rendering of any and all objects (probably should specialize for 2D and 3D objects)
  // this should also hold (a point perhaps) to the camera that is being used by the system
  struct Renderer_NEW
  {
    // should contain the logic that is currently in the shader and the render object
    void DrawMesh(const Context& context) const;
    void DrawMesh(const SkinnedContext& context) const;

  private:
    Shader_NEW _currentShader; // used for tracking shader changes and ordering information

    // is this needed?
    void _Draw(const Context& context) const;

    void _DrawLines(Core::size vertexCount) const;
    void _DrawTriangles(Core::size vertexCount) const;

    void _SetShaderVariables(const Context& context) const;
    void _SetShaderVariables(const SkinnedContext& context) const;
    void _SetMaterialContext(const Material_NEW& material) const;

    void _SetShader(const Shader_NEW& shader);
  };
}// namespace Rendering
}// namespace Application