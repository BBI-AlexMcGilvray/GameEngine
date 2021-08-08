#pragma once

#include "Core/Headers/Exception.h"

using namespace Core;

namespace Data
{
	namespace SQL
	{
		struct SQLException : Exception
		{
			using Exception::Exception;
		};

		struct InvalidDB : SQLException
		{
			using SQLException::SQLException;
		};
	}
}