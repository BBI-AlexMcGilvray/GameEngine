#pragma once

#include "Core/Headers/CoreDefs.h"
#include "Core/Headers/ListDefs.h"

#include "Data/Headers/AssetName.h"

#include "Data/Rendering/Headers/MaterialData.h"
#include "Data/Rendering/Headers/StaticMeshData.h"
#include "Data/Rendering/Headers/SkeletonData.h"
#include "Data/Rendering/Headers/TextureData.h"

using namespace Core;

namespace Data
{
	namespace Rendering
	{
		// holds the information about the mesh of a 3D object
		struct StaticModelData
		{
			AssetName<MaterialData> Material;
			AssetName<StaticMeshData> Mesh;
			AssetName<SkeletonData> Skeleton;
			AssetName<TextureData> Texture;

			StaticModelData() = default;
			StaticModelData(AssetName<StaticModelData> asset);
		};
	}

	template <>
	struct AssetType<Rendering::StaticModelData>
	{
		static Hash ClassHash()
		{
			return HashValue("StaticModelData");
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