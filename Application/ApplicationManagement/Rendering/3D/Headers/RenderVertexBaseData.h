#pragma once

#include "Data/Rendering/Headers/VertexBaseData.h"

using namespace Core::Math;

namespace Application
{
	namespace Rendering
	{
		struct SimpleVertexRenderDataBase
		{
			Float3 Position; // standard vertex attribute
			Float3 Normal; // vertex normal

			SimpleVertexRenderDataBase()
			{}

			SimpleVertexRenderDataBase(const Data::Rendering::SimpleVertexDataBase& data)
				: SimpleVertexRenderDataBase(data.Position, data.Normal)
			{}

			SimpleVertexRenderDataBase(const Float3& pos, const Float3& normal)
			{
				Position = pos;
				Normal = normal;
			}
		};

		struct VertexRenderDataBase
		{
			Float3 Position; // standard vertex attribute
			Float3 Normal; // vertex normal
			Float2 UVs; // vertex uvs

			VertexRenderDataBase()
			{}

			VertexRenderDataBase(const Data::Rendering::VertexDataBase& data)
				: VertexRenderDataBase(data.Position, data.Normal, data.UVs)
			{}

			VertexRenderDataBase(const Float3& pos, const Float3& normal, const Float2& uvs)
			{
				Position = pos;
				Normal = normal;
				UVs = uvs;
			}
		};

		struct AnimatedVertexRenderDataBase
		{
			Float3 Position; // standard vertex attribute
			Float3 Normal; // vertex normal
			//Float2 UVs; // vertex uvs
			Float4 BoneWeight;
			Int4 BoneIndices;

			AnimatedVertexRenderDataBase()
			{}

			AnimatedVertexRenderDataBase(const Data::Rendering::AnimatedVertexDataBase& data)
				: AnimatedVertexRenderDataBase(data.Position, data.Normal, data.UVs, Int4(0), data.BoneWeight)
			{}

			AnimatedVertexRenderDataBase(const Float3& pos, const Float3& normal, const Float2& uvs, const Int4& boneIndices, const Float4& boneWeight)
			{
				Position = pos;
				Normal = normal;
				//UVs = uvs;
				BoneWeight = boneWeight;
				BoneIndices = boneIndices;
			}
		};
	}
}
