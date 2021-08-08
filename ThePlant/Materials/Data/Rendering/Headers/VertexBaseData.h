#pragma once

#include "Core/Debugging/Headers/Macros.h"
#include "Core/Math/Headers/Vector2.h"
#include "Core/Math/Headers/Vector3.h"
#include "Core/Math/Headers/Vector4.h"

using namespace Core::Math;

namespace Data {
namespace Rendering {
  struct SimpleVertexDataBase
  {
    Float3 Position;// standard vertex attribute
    Float3 Normal;// vertex normal

    SimpleVertexDataBase()
    {}

    SimpleVertexDataBase(const Float3 &pos, const Float3 &normal)
    {
      Position = pos;
      Normal = normal;
    }
  };

  struct VertexDataBase
  {
    Float3 Position;// standard vertex attribute
    Float3 Normal;// vertex normal
    Float2 UVs;// vertex uvs

    VertexDataBase()
    {}

    VertexDataBase(const Float3 &pos, const Float3 &normal, const Float2 &uvs)
    {
      Position = pos;
      Normal = normal;
      UVs = uvs;
    }
  };

  struct AnimatedVertexDataBase
  {
    Float3 Position;// standard vertex attribute
    Float3 Normal;// vertex normal
    Float2 UVs;// vertex uvs
    List<String> BoneName;
    Float4 BoneWeight;

    AnimatedVertexDataBase()
    {}

    AnimatedVertexDataBase(const Float3 &pos, const Float3 &normal, const Float2 &uvs, const List<String> &boneName, const Float4 &boneWeight)
    {
      ASSERT(boneName.size() == 4);
      Position = pos;
      Normal = normal;
      UVs = uvs;
      BoneName = boneName;
      BoneWeight = boneWeight;
    }
  };
}// namespace Rendering
}// namespace Data