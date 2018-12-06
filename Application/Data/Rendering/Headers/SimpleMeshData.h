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
		struct SimpleMeshData
		{
			List<SimpleVertexDataBase> Vertices;
			uint VertexCount = 0;

			SimpleMeshData() = default;
			SimpleMeshData(String fileName);
		};
	}

	template <>
	struct AssetType<Rendering::SimpleMeshData>
	{
		Hash ClassHash() const
		{
			return HashValue("SimpleMeshData");
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