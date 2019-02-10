#pragma once

#include "Core/Headers/CoreDefs.h"
#include "Core/Headers/ListDefs.h"

#include "Data/Headers/AssetName.h"

#include "Data/Rendering/Headers/MaterialData.h"
#include "Data/Rendering/Headers/AnimatedMeshData.h"
#include "Data/Rendering/Headers/SkeletonData.h"
#include "Data/Rendering/Headers/TextureData.h"

using namespace Core;

namespace Data
{
	namespace Rendering
	{
		// holds the information about the mesh of a 3D object
		struct AnimatedModelData
		{
			AssetName<MaterialData> Material;
			AssetName<AnimatedMeshData> Mesh;
			AssetName<SkeletonData> Skeleton;
			AssetName<TextureData> Texture;

			AnimatedModelData() = default;
			AnimatedModelData(AssetName<AnimatedModelData> asset);
		};
	}

	template <>
	struct AssetType<Rendering::AnimatedModelData>
	{
		static Hash ClassHash()
		{
			return HashValue("AnimatedModelData");
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