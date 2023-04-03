#include "Pipeline\Rendering\Renderer.h"

#include "Materials/Core/Debugging/Headers/Macros.h"

#include "Dependencies/Includes/glew.h"

using namespace Core;

namespace Application {
namespace Rendering {
  const std::string TAG = "Renderer";

  // have not yet confirmed this works, but it should set the given variables to the provided values if they exist in the shader
  // as for how we can guarantee/determine what shader variables exist for consistency/debugging, TBD - maybe there is a OpenGL call?
  //  - see: https://stackoverflow.com/questions/440144/in-opengl-is-there-a-way-to-get-a-list-of-all-uniforms-attribs-used-by-a-shade
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

  Renderer::Renderer(ShaderManager& shaderManager, CameraManager& cameraManager, MeshManager& meshManager)
  : _cameraManager(cameraManager)
  , _shaderManager(shaderManager)
  , _meshManager(meshManager)
  {}

  void Renderer::StartFrame()
  {
  #ifdef DEBUG
    _ResetTrackingInfo();
  #endif
  }

  void Renderer::EndFrame()
  {
  #ifdef DEBUG
    // _PrintTrackingInfo(); // only print if needed for debugging (in the future this can be used with an IMGUI window - the window could be a Logger implementation based on tag?)
  #endif
  }

  void Renderer::SetShader(const RenderDataHandle& shader)
  {
    if (_currentShader != nullptr && _currentShader->IsHeldBy(shader))
    {
      return;
    }

  #ifdef DEBUG
    _trackingInfo.shadersUsed += 1;
  #endif
    _currentShader = &(_shaderManager.GetShader(shader));
    glUseProgram(_currentShader->glProgram.Object);
  }

  void Renderer::ClearShader()
  {
    _currentShader = nullptr;
    glUseProgram(0);
  }

  void Renderer::SetRenderTarget(const RenderDataHandle& renderTarget, const Core::Math::Color& clearColour)
  {
    if (_currentTarget != nullptr && _currentTarget->IsHeldBy(renderTarget))
    {
      return;
    }

  #ifdef DEBUG
    _trackingInfo.renderTargetsUsed += 1;
  #endif
    _currentTarget = &(_cameraManager.GetValidRenderTarget(renderTarget));

    _currentTarget->frameBuffer.Bind();
    glEnable(GL_DEPTH_TEST);
    glClearColor(clearColour.R, clearColour.G, clearColour.B, clearColour.A);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
  }

  void Renderer::ClearRenderTarget()
  {
    _currentTarget->frameBuffer.Unbind();
    _currentTarget = nullptr;
  }

  void Renderer::DrawMesh(const Context& context)
  {
  #ifdef DEBUG
    _trackingInfo.modelsDrawn += 1;
    _SetDrawMode(context);
  #endif
    _SetShaderVariables(context);
    _Draw(context);
  }

  void Renderer::DrawMesh(const SkinnedContext& context)
  {
  #ifdef DEBUG
    _trackingInfo.skinnedModelsDrawn += 1;
    _SetDrawMode(context.context);
  #endif
    _SetShaderVariables(context);
    _Draw(context.context);
  }

  void Renderer::_Draw(const Context& context)
  {
    DEBUG_ASSERT(_currentShader->IsHeldBy(context.material.shader));
    if (_currentMesh == nullptr || !_currentMesh->IsHeldBy(context.mesh))
    {
      _currentMesh = &(_meshManager.GetMesh(context.mesh));
    }
    _currentMesh->buffer.Bind(); // mesh should have GLBuffer, when would need to get bound
  #ifdef DEBUG
    switch (context.type)
    {
      case DrawType::LINE:
      {
        _DrawLines(_currentMesh->vertices);
        break;
      }
      case DrawType::TRIANGLE:
      {
  #endif
        _DrawTriangles(_currentMesh->vertices);
  #ifdef DEBUG
        break;
      }
    }
  #endif
    // don't unbind so mesh re-use is more efficient
    // context.mesh.buffer.Unbind();
  }

  void Renderer::_DrawLines(Core::size vertexCount) const
  {
  #ifdef DEBUG
    _trackingInfo.drawCalls += 1;
  #endif
    DEBUG_ASSERT((INT32_MAX >= vertexCount));
    glDrawArrays(GL_LINE_STRIP, 0, GLsizei(vertexCount));
  }

  void Renderer::_DrawTriangles(Core::size vertexCount) const
  {
  #ifdef DEBUG
    _trackingInfo.drawCalls += 1;
  #endif
    DEBUG_ASSERT((INT32_MAX >= vertexCount));
    glDrawArrays(GL_TRIANGLES, 0, GLsizei(vertexCount));
  }

#if DEBUG
  void Renderer::_SetDrawMode(const Context& context) const
  {
    // the FRONT_AND_BACK may be the render issue cause?
    switch (context.mode)
    {
      case DrawMode::FILL:
      {
        glPolygonMode(GL_FRONT_AND_BACK, GL_FILL); // 'regular' rendering
        break;
      }
      case DrawMode::LINE:
      {
        glPolygonMode(GL_FRONT_AND_BACK, GL_LINE); // wireframe mode
        break;
      }
    }
  }
#endif

  void Renderer::_SetShaderVariables(const Context& context) const
  {
    VERIFY(_currentShader != nullptr);
    GLuint program = _currentShader->glProgram.Object;

    // set the required information that needs to be used in the shader
    GLint MVP = glGetUniformLocation(program, "MVP");
    glUniformMatrix4fv(MVP, 1, GL_FALSE, (GLfloat *)&(context.mvp.E1E2E3E4[0]));

    // assign color to shader
    GLint modColor = glGetUniformLocation(program, "modColor");
    glUniform4fv(modColor, 1, &(context.color.RGBA[0]));

    _SetMaterialContext(context.material);
  }

  void Renderer::_SetShaderVariables(const SkinnedContext& context) const
  {
    VERIFY(_currentShader != nullptr);
    GLuint program = _currentShader->glProgram.Object;

    DEBUG_ASSERT(context.bones.size() <= 50);
    GLint boneMatrices = glGetUniformLocation(program, "boneMatrices");
    glUniformMatrix4fv(boneMatrices, static_cast<GLsizei>(context.bones.size()), GL_FALSE, (GLfloat *)&(context.bones[0].E1.X));

    _SetShaderVariables(context.context);
  }

  void Renderer::_SetMaterialContext(const Material& material) const
  {
    VERIFY(_currentShader->IsHeldBy(material.shader));
    for (const auto& context : material.shaderContext)
    {
      const auto& name = context.first;
      GLint glLocation = glGetUniformLocation(_currentShader->glProgram.Object, name.c_str());

      GLVisitor visitor(glLocation);
      std::visit(visitor, context.second);
    }
  }

#ifdef DEBUG
  void Renderer::_ResetTrackingInfo() const
  {
    _trackingInfo = TrackingInfo();
  }

  void Renderer::_PrintTrackingInfo() const
  {
    CORE_LOG(TAG, "renderTargetsUsed = " + std::to_string(_trackingInfo.renderTargetsUsed));
    CORE_LOG(TAG, "shadersUsed = " + std::to_string(_trackingInfo.shadersUsed));
    CORE_LOG(TAG, "drawCalls = " + std::to_string(_trackingInfo.drawCalls));
    CORE_LOG(TAG, "modelsDrawn = " + std::to_string(_trackingInfo.modelsDrawn));
    CORE_LOG(TAG, "skinnedModelsDrawn = " + std::to_string(_trackingInfo.skinnedModelsDrawn));
  }
#endif
}// namespace Rendering
}// namespace Application