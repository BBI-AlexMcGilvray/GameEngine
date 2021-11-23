#pragma once

#include "Data/Headers/AssetMacros.h"

namespace Data {
namespace Rendering {
  ASSET(VertexShaderData,
    (std::string) shaderCode
  );

  ASSET(FragmentShaderData,
    (std::string) shaderCode
  );

  ASSET(ShaderData,
    (std::string) name,
    (AssetName<VertexShaderData>) vertexShader,
    (AssetName<FragmentShaderData>) fragmentShader
  );
}// namespace Rendering

ASSET_TYPE(Rendering::VertexShaderData, "Resources/Shaders/Vertex/", ".vshd");
ASSET_TYPE(Rendering::FragmentShaderData, "Resources/Shaders/Fragment/", ".fshd");
ASSET_TYPE(Rendering::ShaderData, "Resources/Shaders/", ".shd");
}// namespace Data