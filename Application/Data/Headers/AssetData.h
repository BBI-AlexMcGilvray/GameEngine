#pragma once

#include "Core/Headers/Hash.h"

#include "Data/Headers/AssetName.h"

using namespace Core;

namespace Data
{
	template <typename T>
	struct AssetData
	{
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