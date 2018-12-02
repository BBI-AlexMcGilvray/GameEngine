#pragma once

#include "Core/Headers/Exception.h"

using namespace Core;

namespace Data
{
	struct AssetException : Exception
	{
		using Exception::Exception;
	};

	struct InvalidAsset : AssetException
	{
		using AssetException::AssetException;
	};
}