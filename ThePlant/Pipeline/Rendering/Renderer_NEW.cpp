#include "Pipeline\Rendering\Headers\Renderer_NEW.h"

#include "Pipeline/Rendering/Headers/RenderObjectBase.h"

#include "Dependencies/Includes/glew.h"

using namespace Core;

namespace Application {
namespace Rendering {
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
    _SetShader(context.material.Shader); // we should set shader values by storing a collection of <string, value> pairs (since we need to set shader values by name)
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
  }

  void Renderer_NEW::_SetShaderVariables(const SkinnedContext& context) const
  {
    GLuint program = _currentShader->Object;

    VERIFY(context.bones.size() <= 50);
    GLint boneMatrices = glGetUniformLocation(program, "boneMatrices");
    glUniformMatrix4fv(boneMatrices, static_cast<GLsizei>(context.bones.size()), GL_FALSE, (GLfloat *)&(context.bones[0].E1.X));

    _SetShaderVariables(context.context);
  }

  void Renderer_NEW::_SetShader(const ShaderBase& shader)
  {
    if (_currentShader == &shader)
    {
      return;
    }

    _currentShader = &shader;
  }
}// namespace Rendering
}// namespace Application