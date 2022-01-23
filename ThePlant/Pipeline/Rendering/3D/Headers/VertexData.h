#pragma once

#include <array>
#include <string>
#include <vector>

#include "Core/Math/Headers/Vector2.h"
#include "Core/Math/Headers/Vector3.h"
#include "Core/Math/Headers/Vector4.h"
#include "Core/Headers/Macros.h"

#include "Data/Rendering/Headers/AnimatedMeshData.h"
#include "Data/Rendering/Headers/SimpleMeshData.h"
#include "Data/Rendering/Headers/SkeletonData.h"
#include "Data/Rendering/Headers/StaticMeshData.h"

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
    std::array<std::string, 4> boneName;
    Core::Math::Float4 boneWeight;
  };

  // use this once the AnimatedVertexData can map the boneName values to indices of a given skeleton
  struct SkinnedVertexData
  {
    Core::Math::Float3 position;
    Core::Math::Float3 normal;
    Core::Math::Float2 uvs;
    Core::Math::Float4 boneIndices; // float because shader had issues reading as ints
    Core::Math::Float4 boneWeight;

    SkinnedVertexData() = default;
    SkinnedVertexData(const SkinnedVertexData& other) = default;
    ~SkinnedVertexData() = default;

    SkinnedVertexData(const AnimatedVertexData& other)
    {
      position = other.position;
      normal = other.normal;
      uvs = other.uvs;
      boneIndices = Core::Math::Float4();
      boneWeight = other.boneWeight;
    }
  };
  
  std::vector<SimpleVertexData> createRuntimeData(const Data::Rendering::SimpleMeshData& meshData);
  std::vector<VertexData> createRuntimeData(const Data::Rendering::StaticMeshData& meshData);
  std::vector<AnimatedVertexData> createExplicitRuntimeData(const Data::Rendering::AnimatedMeshData& meshData);
  SkinnedVertexData SkinToSkeleton(const AnimatedVertexData& vertexData, const Data::Rendering::SkeletonData& skeleton);
  std::vector<SkinnedVertexData> createRuntimeData(const std::vector<AnimatedVertexData>& animatedData, const Data::Rendering::SkeletonData& skeleton);
  std::vector<SkinnedVertexData> createRuntimeData(const Data::Rendering::AnimatedMeshData& meshData, const Data::Rendering::SkeletonData& skeleton);
}// namespace Rendering
}// namespace Application