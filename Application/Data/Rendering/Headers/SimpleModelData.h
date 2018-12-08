#pragma once

#include "Core/Headers/CoreDefs.h"
#include "Core/Headers/ListDefs.h"

#include "Data/Headers/AssetName.h"

#include "Data/Rendering/Headers/MaterialData.h"
#include "Data/Rendering/Headers/SimpleMeshData.h"
#include "Data/Rendering/Headers/TextureData.h"

using namespace Core;

namespace Data
{
	namespace Rendering
	{
		// holds the information about the mesh of a 3D object
		struct SimpleModelData
		{
			AssetName<MaterialData> Material;
			AssetName<SimpleMeshData> Mesh;
			AssetName<TextureData> Texture;

			SimpleModelData() = default;
			SimpleModelData(AssetName<SimpleModelData> asset);
		};
	}

	template <>
	struct AssetType<Rendering::SimpleModelData>
	{
		static Hash ClassHash()
		{
			return HashValue("SimpleModelData");
		}

		static String GetPath()
		{
			return "Resources/Models/";
		}

		static String GetFileType()
		{
			return ".mdl";
		}
	};
}