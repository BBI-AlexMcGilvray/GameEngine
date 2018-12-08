#pragma once

#include "Core/Headers/Hash.h"

#include "Data/Headers/AssetExceptions.h"

using namespace Core;

namespace Data
{
	template <typename T>
	struct AssetType
	{
		static Hash ClassHash()
		{
			return HashValue("void");
		}

		static String GetPath()
		{
			return "";
		}

		static String GetFileType()
		{
			return "";
		}
	};
}