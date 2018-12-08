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
		struct SimpleMeshData
		{
			List<SimpleVertexDataBase> Vertices;
			uint VertexCount = 0;

			SimpleMeshData() = default;
			SimpleMeshData(AssetName<SimpleMeshData> asset);
		};
	}

	template <>
	struct AssetType<Rendering::SimpleMeshData>
	{
		static Hash ClassHash()
		{
			return HashValue("SimpleMeshData");
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