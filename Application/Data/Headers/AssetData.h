#pragma once

#include "Core/Headers/Hash.h"

#include "Data/Headers/AssetName.h"

using namespace Core;

namespace Data
{
	template <typename T>
	struct AssetData
	{
		// data should likely be a DataPtr<T> that tells the asset manager that the data is referenced so as to not get rid of it
		// for now, the data will just be duplicated
		T Data;
		AssetName<T> Asset;

		AssetData(const AssetData<T>& assetData)
			: Data(assetData.Data), Asset(assetData.Asset)
		{}

		AssetData(const AssetName<T>& assetName, const T& data)
			: Asset(assetName), Data(data)
		{}

		Ptr<T> operator ->()
		{
			return &Data;
		}

		operator T()
		{
			return Data;
		}

		operator AssetName<T>()
		{
			return Asset;
		}
	};
}