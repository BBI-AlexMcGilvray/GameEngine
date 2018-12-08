#pragma once

#include "Core/Math/Headers/Color.h"

#include "Data/Headers/AssetName.h"

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
			MaterialData(AssetName<MaterialData> asset);
		};
	}

	template <>
	struct AssetType<Rendering::MaterialData>
	{
		static Hash ClassHash()
		{
			return HashValue("MaterialData");
		}

		static String GetPath()
		{
			return "Resources/Materials/";
		}

		static String GetFileType()
		{
			return ".mat";
		}
	};
}