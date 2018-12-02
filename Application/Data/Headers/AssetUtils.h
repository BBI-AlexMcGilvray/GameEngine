#pragma once

#include "Core/Headers/CoreDefs.h"

#include "Core/IO/Headers/IODefs.h"
#include "Core/IO/Headers/IOUtils.h"

#include "Data/Headers/AssetData.h"
#include "Data/Headers/AssetName.h"

using namespace Core;
using namespace Core::IO;

namespace Data
{
	template <typename T>
	UniquePtr<AssetData<T>> GetAssetData(AssetName<T> asset)
	{
		FilePath assetPath = asset.GetFilePath();
		assetPath.Path = GetCWD() + assetPath.Path;

		return MakeUnique(AssetData<T>(asset, T(assetPath)));
	};
}