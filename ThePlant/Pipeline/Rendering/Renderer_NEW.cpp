#include "Pipeline\Rendering\Renderer_NEW.h"

#include "Materials/Core/Debugging/Headers/Macros.h"

#include "Dependencies/Includes/glew.h"

using namespace Core;

namespace Application {
namespace Rendering {
  const std::string TAG = "Renderer_NEW";

  struct GLVisitor
  {
    GLVisitor(const GLint& location)
    : location(location)
    {}

    void operator()(const double& val) { glUniform1d(location, val); }

    void operator()(const float& val) { glUniform1f(location, val); }

    void operator()(const int& val) { glUniform1i(location, val); }

    void operator()(const uint& val) { glUniform1ui(location, val); }

    void operator()(const Core::Math::Color& val) { glUniform4fv(location, 1, &(val.RGBA[0])); }

  private:
      const GLint location;
  };

  void Renderer_NEW::StartFrame()
  {
  #ifdef DEBUG
    _ResetTrackingInfo();
  #endif
  }

  void Renderer_NEW::EndFrame()
  {
  #ifdef DEBUG
    _PrintTrackingInfo();
  #endif
  }

  void Renderer_NEW::SetShader(const Shader_NEW& shader)
  {
    if (_currentShader == shader)
    {
      return;
    }

  #ifdef DEBUG
    _trackingInfo.shadersUsed += 1;
  #endif
    _currentShader = shader;
    glUseProgram(_currentShader.glProgram.Object);
  }

  void Renderer_NEW::DrawMesh(const Context& context) const
  {
  #ifdef DEBUG
    _trackingInfo.modelsDrawn += 1;
  #endif
    _SetShaderVariables(context);
    _Draw(context);
  }

  void Renderer_NEW::DrawMesh(const SkinnedContext& context) const
  {
  #ifdef DEBUG
    _trackingInfo.skinnedModelsDrawn += 1;
  #endif
    _SetShaderVariables(context);
    _Draw(context.context);
  }

  void Renderer_NEW::_Draw(const Context& context) const
  {
    VERIFY(context.material.shader == _currentShader);
    context.mesh.buffer.Bind(); // mesh should have GLBuffer, when would need to get bound
    _DrawTriangles(context.mesh.vertices);
    context.mesh.buffer.Unbind();
  }

  void Renderer_NEW::_DrawLines(Core::size vertexCount) const
  {
  #ifdef DEBUG
    _trackingInfo.drawCalls += 1;
  #endif
    VERIFY((INT32_MAX >= vertexCount));
    glDrawArrays(GL_LINE_STRIP, 0, GLsizei(vertexCount));
  }

  void Renderer_NEW::_DrawTriangles(Core::size vertexCount) const
  {
  #ifdef DEBUG
    _trackingInfo.drawCalls += 1;
  #endif
    VERIFY((INT32_MAX >= vertexCount));
    glDrawArrays(GL_TRIANGLES, 0, GLsizei(vertexCount));
  }

  void Renderer_NEW::_SetShaderVariables(const Context& context) const
  {
    GLuint program = _currentShader.glProgram.Object;

    // set the required information that needs to be used in the shader
    GLint MVP = glGetUniformLocation(program, "MVP");
    glUniformMatrix4fv(MVP, 1, GL_FALSE, (GLfloat *)&(context.mvp.E1E2E3E4[0]));

    // assign color to shader
    GLint modColor = glGetUniformLocation(program, "modColor");
    glUniform4fv(modColor, 1, &(context.color.RGBA[0]));

    _SetMaterialContext(context.material);
  }

  void Renderer_NEW::_SetShaderVariables(const SkinnedContext& context) const
  {
    GLuint program = _currentShader.glProgram.Object;

    VERIFY(context.bones.size() <= 50);
    GLint boneMatrices = glGetUniformLocation(program, "boneMatrices");
    glUniformMatrix4fv(boneMatrices, static_cast<GLsizei>(context.bones.size()), GL_FALSE, (GLfloat *)&(context.bones[0].E1.X));

    _SetShaderVariables(context.context);
  }

  void Renderer_NEW::_SetMaterialContext(const Material_NEW& material) const
  {
    for (const auto& context : material.shaderContext)
    {
      const auto& name = context.first;
      const auto& shader = material.shader;
      GLint glLocation = glGetUniformLocation(shader.glProgram.Object, name.c_str());

      GLVisitor visitor(glLocation);
      std::visit(visitor, context.second);
    }
  }

  void Renderer_NEW::_ResetTrackingInfo() const
  {
    _trackingInfo = TrackingInfo();
  }

  void Renderer_NEW::_PrintTrackingInfo() const
  {
    CORE_LOG(TAG, "shadersUsed = " + std::to_string(_trackingInfo.shadersUsed));
    CORE_LOG(TAG, "drawCalls = " + std::to_string(_trackingInfo.drawCalls));
    CORE_LOG(TAG, "modelsDrawn = " + std::to_string(_trackingInfo.modelsDrawn));
    CORE_LOG(TAG, "skinnedModelsDrawn = " + std::to_string(_trackingInfo.skinnedModelsDrawn));
  }
}// namespace Rendering
}// namespace Application