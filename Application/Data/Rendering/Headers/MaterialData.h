#pragma once

#include "Core/Math/Headers/Color.h"

#include "Data/Headers/AssetType.h"

using namespace Core;
using namespace Core::Math;

namespace Data
{
	namespace Rendering
	{
		struct MaterialData
		{
			Color Specular;
			Color Diffuse;
			Color Ambient;
			float Shininess;

			MaterialData() = default;
			MaterialData(String fileName);
		};
	}

	template <>
	struct AssetType<Rendering::MaterialData>
	{
		Hash ClassHash() const
		{
			return HashValue("MaterialData");
		}

		String GetPath() const
		{
			return "Resources/ExportedAssets/Materials/";
		}

		String GetFileType() const
		{
			return ".mat";
		}
	};
}