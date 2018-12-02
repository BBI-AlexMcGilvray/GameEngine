#pragma once

#include "Core/Headers/Hash.h"
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
		AssetType<T> Type;

		FilePath GetFilePath() const
		{
			return FilePath{ Type.GetPath(), String(uint(Name)) + Type.GetFileType() };
		}
		
		AssetName<T>& operator=(Hash name)
		{
			Name = name;

			return (*this);
		}
	};
}