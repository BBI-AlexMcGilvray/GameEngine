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
		AssetType<T> Type;

		AssetName() = default;

		AssetName(Hash hash)
		{
			Name = hash;
		}

		template <typename C>
		AssetName(C&& c)
			: AssetName(HashValue(Forward<C>(c)))
		{
		}
		
		AssetName<T>& operator=(Hash name)
		{
			Name = name;

			return (*this);
		}

		FilePath GetFilePath() const
		{
			return FilePath{ Type.GetPath(), String(uint(Name)) + Type.GetFileType() };
		}
	};
}