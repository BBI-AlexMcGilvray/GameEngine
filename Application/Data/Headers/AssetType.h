#pragma once

#include "Core/Headers/Hash.h"

#include "Data/Headers/AssetExceptions.h"

using namespace Core;

namespace Data
{
	template <typename T>
	struct AssetType
	{
		Hash ClassHash() const
		{
			return HashValue("void");
		}

		String GetPath() const
		{
			return "";
		}

		String GetFileType() const
		{
			return "";
		}
	};
}