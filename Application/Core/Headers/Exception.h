#pragma once

#include "CoreDefs.h"

#include <exception>

namespace Core
{
	struct Exception : std::exception
	{
		Exception();
		Exception(const String& error);
		Exception(const Exception& exception);

		String GetError() const;

	private:
		const String Error;
	};
}