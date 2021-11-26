#pragma once

#include <string>

#include "Dependencies/Includes/glew.h"

#include "Pipeline/Rendering/Shaders/Headers/ObjectShaderBase.h"
#include "Pipeline/Rendering/Shaders/Headers/ShaderBase.h"

#include "Pipeline/Rendering/Shaders/Shader_NEW.h"

using namespace Core;

namespace Application {
namespace Rendering {
  void CreateProgram(Ptr<ObjectShaderBase> objectShader);
  bool CreateShader(Ptr<ShaderBase> shader);

  FragmentShader_NEW CreateFragmentShader(const std::string& shaderCode);
  void DeleteFragmentShader(const FragmentShader_NEW& shader);
  
  VertexShader_NEW CreateVertexShader(const std::string& shaderCode);
  void DeleteVertexShader(const VertexShader_NEW& shader);

  Shader_NEW CreateShader(const VertexShader_NEW& vertexShader, const FragmentShader_NEW& fragmentShader);
  void DeleteShader(const Shader_NEW& shader);
}// namespace Rendering
}// namespace Application