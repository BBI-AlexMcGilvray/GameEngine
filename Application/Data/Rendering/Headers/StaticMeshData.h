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
		struct StaticMeshData
		{
			List<VertexDataBase> Vertices;
			uint VertexCount = 0;

			StaticMeshData() = default;
			StaticMeshData(AssetName<StaticMeshData> asset);
		};
	}

	template <>
	struct AssetType<Rendering::StaticMeshData>
	{
		static Hash ClassHash()
		{
			return HashValue("StaticMeshData");
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