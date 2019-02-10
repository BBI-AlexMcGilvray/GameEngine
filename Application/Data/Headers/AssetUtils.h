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
	// in the future, this should probably return a DataPtr<T> that loads from the asset manager if the asset is already loaded and increments referenced
	// to diminish on reloading and duplicating data
	// ACTUALLY, would not need to be DataPtr<T>, but instead AssetData should be the 'DataPtr' class
	template <typename T>
	UniquePtr<AssetData<T>> GetAssetData(AssetName<T> asset)
	{
		return MakeUnique<AssetData<T>>(asset);
	};
}