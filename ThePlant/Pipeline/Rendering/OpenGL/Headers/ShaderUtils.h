#pragma once

#include <string>

#include "Core/Headers/PtrDefs.h"

#include "Dependencies/Includes/glew.h"

#include "Pipeline/Rendering/Shaders/Shader.h"

using namespace Core;

namespace Application {
namespace Rendering {
  FragmentShader CreateFragmentShader(const std::string& shaderCode);
  void DeleteFragmentShader(const FragmentShader& shader);
  
  VertexShader CreateVertexShader(const std::string& shaderCode);
  void DeleteVertexShader(const VertexShader& shader);

  void CreateShader(ShaderData& shader, const VertexShader& vertexShader, const FragmentShader& fragmentShader);
  void DeleteShader(ShaderData& shader);
}// namespace Rendering
}// namespace Application