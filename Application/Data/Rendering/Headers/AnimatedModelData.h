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
			AnimatedModelData(String fileName);
		};
	}

	/*
	template <>
	struct AssetType<Rendering::AnimatedModelData>
	{
		Hash ClassHash() const
		{
			return HashValue("AnimatedModelData");
		}

		String GetPath() const
		{
			return "Resources/ExportedAssets/Models/";
		}

		String GetFileType() const
		{
			return ".AMdl";
		}
	};
	*/
}