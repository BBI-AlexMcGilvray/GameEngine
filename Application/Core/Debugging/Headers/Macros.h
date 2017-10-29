#pragma once

#include <cstdlib>
#include <iostream>
#include <cassert>
#include <string>

#include "Declarations.h"

namespace Core
{
	inline void Message(std::string message)
	{
		if (GLOBAL_EXPLICIT)
		{
			std::cout << message << std::endl;
		}
		assert(false);
	}

	inline bool VerifyCondition(bool condition, bool runAssert)
	{
		bool result = condition;

		if (GLOBAL_EXPLICIT)
		{
			std::cout << "X was " << (result ? "TRUE" : "FALSE") << std::endl;
		}

		if (runAssert)
		{
			assert(result);
		}
		return result;
	}

	inline void VerifyMessage(bool condition, std::string message, bool runAssert)
	{
		bool conditionResult = VerifyCondition(condition, runAssert);

		if (!conditionResult)
		{
			Message(message);
		}
	}

	#if DEBUG
	#define VERIFY( X ) VerifyCondition( X, true )
	#else
	#define VERIFY( X ) // do nothing if not debugging
	#endif

	#if DEBUG
	#define MESSAGE( X, M ) VerifyMessage( X, M, true )
	#else
	#define MESSAGE( X, M ) // do nothing
	#endif
}