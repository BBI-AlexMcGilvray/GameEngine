#include "Pipeline\Rendering\Headers\Renderer_NEW.h"

#include "Pipeline/Rendering/Headers/RenderObjectBase.h"

#include "Dependencies/Includes/glew.h"

using namespace Core;

namespace Application {
namespace Rendering {
  void Renderer_NEW::DrawMesh(const Context& context) const
  {
    _SetShader(context.material.Shader);
    _SetShaderVariables(context);
    _Draw(context);
  }

  void Renderer_NEW::DrawMesh(const SkinnedContext& context) const
  {
    _SetShader(context.context.material.Shader);
    _SetShaderVariables(context);
    _Draw(context.context);
  }

  void Renderer_NEW::_Draw(const Context& context) const
  {
    context.mesh.Buffer.Bind(); // mesh should have GLBuffer, when would need to get bound
    _DrawTriangles(context.vertices);
  }

  void Renderer_NEW::_DrawLines(Core::size vertexCount) const
  {
    VERIFY((INT32_MAX >= vertexCount));
    glDrawArrays(GL_LINE_STRIP, 0, GLsizei(vertexCount));
  }

  void Renderer_NEW::_DrawTriangles(Core::size vertexCount) const
  {
    VERIFY((INT32_MAX >= vertexCount));
    glDrawArrays(GL_TRIANGLES, 0, GLsizei(vertexCount));
  }

  void Renderer_NEW::_SetShaderVariables(const Context& context) const
  {
    GLuint program = _currentShader->Object;

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
    GLuint program = _currentShader->Object;

    VERIFY(context.bones.size() <= 50);
    GLint boneMatrices = glGetUniformLocation(program, "boneMatrices");
    glUniformMatrix4fv(boneMatrices, static_cast<GLsizei>(context.bones.size()), GL_FALSE, (GLfloat *)&(context.bones[0].E1.X));

    _SetShaderVariables(context.context);
  }

  void Renderer_NEW::_SetMaterialContext(const Material_NEW& material) const
  {
    for (const auto& context : material.shaderContext)
    {
      std::visit([name = context.first, shader = material.shader](const double& val)
      {
        GLint doubleLocation = glGetUniformLocation(shader.glProgram, name);
        glUniform1d(doubleLocation, val);
      }, [name = context.first](const float& val)
      {
        GLint floatLocation = glGetUniformLocation(shader.glProgram, name);
        glUniform1f(floatLocation, val);
      }, [name = context.first](const int& val)
      {
        GLint intLocation = glGetUniformLocation(shader.glProgram, name);
        glUniform1i(intLocation, val);
      }, [name = context.first](const uint& val)
      {
        GLint uintLocation = glGetUniformLocation(shader.glProgram, name);
        glUniform1ui(uintLocation, val);
      }, [name = context.first](const Core::Math::Color& val)
      {
        GLint colorLocation = glGetUniformLocation(shader.glProgram, name);
        glUniform4fv(colorLocation, 1, &(val.RGBA[0]));
      }, context.second);
    }
  }

  void Renderer_NEW::_SetShader(const Shader_NEW& shader)
  {
    if (_currentShader == &shader)
    {
      return;
    }

    _currentShader = &shader;
    glUseProgram(_currentShader.glProgram.Object);
  }
}// namespace Rendering
}// namespace Application