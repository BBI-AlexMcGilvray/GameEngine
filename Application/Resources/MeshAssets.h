#pragma once

#include "Data/Headers/AssetType.h"

#include "Data/Rendering/Headers/MeshData.h"

namespace Data
{
	struct AssetType<Rendering::MeshData>
	{
		Hash ClassHash() const
		{
			return Core::HashValue("MeshAsset");
		}

		String GetPath() const
		{
			return "Meshes/";
		}

		String GetFileType() const
		{
			return ".msh";
		}
	};
}