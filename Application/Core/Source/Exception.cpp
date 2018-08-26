#pragma once

#include "Core/Headers/Exception.h"

namespace Core
{
	Exception::Exception()
		: Error("")
	{}

	Exception::Exception(const String& error)
		: Error(error)
	{}

	Exception::Exception(const Exception& exception)
		: Error(exception.GetError())
	{}

	String Exception::GetError() const
	{
		return Error;
	}
}