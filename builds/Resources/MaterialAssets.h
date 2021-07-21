#pragma once

#include "Data/Headers/AssetType.h"

#include "Data/Rendering/Headers/MaterialData.h"

namespace Data
{
	struct AssetType<Rendering::MaterialData>
	{
		Hash ClassHash() const
		{
			return Core::HashValue("MaterialAsset");
		}

		String GetPath() const
		{
			return "Materials/";
		}

		String GetFileType() const
		{
			return ".mat";
		}
	};
}