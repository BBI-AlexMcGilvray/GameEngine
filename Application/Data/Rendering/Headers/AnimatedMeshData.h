#pragma once

#include "Core/Headers/CoreDefs.h"
#include "Core/Headers/ListDefs.h"

#include "Data/Headers/AssetName.h"

#include "Data/Rendering/Headers/VertexBaseData.h"

using namespace Core;

namespace Data
{
	namespace Rendering
	{
		// holds the information about the mesh of a 3D object
		struct AnimatedMeshData
		{
			List<AnimatedVertexDataBase> Vertices;
			uint VertexCount = 0;

			AnimatedMeshData() = default;
			AnimatedMeshData(AssetName<AnimatedMeshData> asset);
		};
	}

	template <>
	struct AssetType<Rendering::AnimatedMeshData>
	{
		static Hash ClassHash()
		{
			return HashValue("AnimatedMeshData");
		}

		static String GetPath()
		{
			return "Resources/Meshes/";
		}

		static String GetFileType()
		{
			return ".msh";
		}
	};
}