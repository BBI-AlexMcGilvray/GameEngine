#pragma once

#include <string>
#include <vector>

#include "Core/Math/Headers/Vector2.h"
#include "Core/Math/Headers/Vector3.h"
#include "Core/Math/Headers/Vector4.h"
#include "Core/Headers/Macros.h"

#include "Data/Rendering/Headers/SimpleMeshData.h"
#include "Data/Rendering/Headers/StaticMeshData.h"
#include "Data/Rendering/Headers/AnimatedMeshData.h"

namespace Application {
namespace Rendering {
  struct SimpleVertexData
  {
    Core::Math::Float3 position;
    Core::Math::Float3 normal;
  };

  struct VertexData
  {
    Core::Math::Float3 position;
    Core::Math::Float3 normal;
    Core::Math::Float2 uvs;
  };

  struct AnimatedVertexData
  {
    Core::Math::Float3 position;
    Core::Math::Float3 normal;
    Core::Math::Float2 uvs;
    std::vector<std::string> boneName;
    Core::Math::Float4 boneWeight;
  };
  
  std::vector<SimpleVertexData> createRuntimeData(const Data::Rendering::SimpleMeshData& meshData);
  std::vector<VertexData> createRuntimeData(const Data::Rendering::StaticMeshData& meshData);
  std::vector<AnimatedVertexData> createRuntimeData(const Data::Rendering::AnimatedMeshData& meshData);
}// namespace Rendering
}// namespace Application