#pragma once

#include "Core/Headers/CoreDefs.h"
#include "Core/Headers/ListDefs.h"

#include "Data/Headers/AssetType.h"

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
			AnimatedMeshData(String fileName);
		};
	}

	/*
	template <>
	struct AssetType<Rendering::AnimatedMeshData>
	{
		Hash ClassHash() const
		{
			return HashValue("AnimatedMeshData");
		}

		String GetPath() const
		{
			return "Resources/ExportedAssets/Meshes/";
		}

		String GetFileType() const
		{
			return ".AMsh";
		}
	};
	*/
}