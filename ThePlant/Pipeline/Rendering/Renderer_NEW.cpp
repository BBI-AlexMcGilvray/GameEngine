#include "Pipeline\Rendering\Renderer_NEW.h"

#include "Materials/Core/Debugging/Headers/Macros.h"

#include "Dependencies/Includes/glew.h"

using namespace Core;

namespace Application {
namespace Rendering {
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
    DEBUG_LOG("Renderer_NEW", "Starting frame with " + std::to_string(_drawCalls) + " draw calls");
  }

  void Renderer_NEW::EndFrame()
  {
    DEBUG_LOG("Renderer_NEW", "Ending frame with " + std::to_string(_drawCalls) + " draw calls");
    _drawCalls = 0;
  }

  void Renderer_NEW::SetShader(const Shader_NEW& shader)
  {
    if (_currentShader == shader)
    {
      return;
    }

    _currentShader = shader;
    glUseProgram(_currentShader.glProgram.Object);
  }

  void Renderer_NEW::DrawMesh(const Context& context) const
  {
    _SetShaderVariables(context);
    _Draw(context);
  }

  void Renderer_NEW::DrawMesh(const SkinnedContext& context) const
  {
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
    ++_drawCalls;
    VERIFY((INT32_MAX >= vertexCount));
    glDrawArrays(GL_LINE_STRIP, 0, GLsizei(vertexCount));
  }

  void Renderer_NEW::_DrawTriangles(Core::size vertexCount) const
  {
    ++_drawCalls;
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

      // std::visit([name, shader, glLocation](const double& val)
      // {
      //   glUniform1d(glLocation, val);
      // }, [name, shader, glLocation](const float& val)
      // {
      //   glUniform1f(glLocation, val);
      // }, [name, shader, glLocation](const int& val)
      // {
      //   glUniform1i(glLocation, val);
      // }, [name, shader, glLocation](const uint& val)
      // {
      //   glUniform1ui(glLocation, val);
      // }, [name, shader, glLocation](const Core::Math::Color& val)
      // {
      //   glUniform4fv(glLocation, 1, &(val.RGBA[0]));
      // }, context.second);
      GLVisitor visitor(glLocation);
      std::visit(visitor, context.second);
    }
  }
}// namespace Rendering
}// namespace Application