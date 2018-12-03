#pragma once

#include "Core/Headers/CoreDefs.h"
#include "Core/Headers/ListDefs.h"

#include "Data\Headers\AssetType.h"

#include "Data/Rendering/Headers/VertexBaseData.h"

using namespace Core;

namespace Data
{
	namespace Rendering
	{
		// holds the information about the mesh of a 3D object
		struct StaticMeshData
		{
			List<VertexDataBase> Vertices;
			uint VertexCount = 0;

			StaticMeshData() = default;
			StaticMeshData(String fileName);
		};
	}

	template <>
	struct AssetType<Rendering::StaticMeshData>
	{
		Hash ClassHash() const
		{
			return HashValue("StaticMeshData");
		}

		String GetPath() const
		{
			return "Resources/ExportedAssets/Meshes/";
		}

		String GetFileType() const
		{
			return ".msh";
		}
	};
}