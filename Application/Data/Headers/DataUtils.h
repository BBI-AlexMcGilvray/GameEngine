#pragma once

#include "Core/Headers/CoreDefs.h"

#include "Data/IO/Headers/IOUtils.h"

using namespace Core;

namespace Data
{
	template <typename T>
	T GetData(String fileName)
	{
		String assetPath = IO::GetCWD() + "/Data/Assets/" + fileName;

		return T(assetPath);
	}
}