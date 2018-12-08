#pragma once

#include "Core/Headers/Hash.h"
#include "Core/Headers/TemplateDefs.h"
#include "Core/IO/Headers/IODefs.h"

#include "Data/Headers/AssetType.h"

using namespace Core;
using namespace Core::IO;

namespace Data
{
	template <typename T>
	struct AssetName
	{
		Hash Name;

		AssetName() = default;

		AssetName(const AssetName<T>& aN)
			: Name(aN.Name)
		{}

		AssetName(const uint& u)
			: AssetName(Hash(u))
		{}

		AssetName(const Hash& hash)
			: Name(hash)
		{
		}

		AssetName<T>& operator=(const AssetName<T> aN)
		{
			Name = aN.Name;

			return (*this);
		}
		
		AssetName<T>& operator=(const Hash& name)
		{
			Name = name;

			return (*this);
		}

		FilePath GetFilePath() const
		{
			return FilePath{ GetCWD() + AssetType<T>::GetPath(), ToString(uint(Name)) + AssetType<T>::GetFileType() };
		}
	};
}