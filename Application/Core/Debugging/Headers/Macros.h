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
		std::cout << message << std::endl;
	}

	inline bool VerifyCondition(bool condition, std::string conditionString)
	{
		bool result = condition;

		if (GLOBAL_EXPLICIT && !result && conditionString != "")
		{
			Message(conditionString);
		}
		
		return result;
	}

	inline bool VerifyMessage(bool condition, std::string message)
	{
		return VerifyCondition(condition, message);
	}

	#if DEBUG
#define VERIFY( X ) VerifyCondition( X, #X )
	#else
	#define VERIFY( X ) // do nothing if not debugging
	#endif

	#if DEBUG
	#define MESSAGE( X, M ) VerifyMessage( X, M )
	#else
	#define MESSAGE( X, M ) // do nothing
	#endif

	#if DEBUG
	#define ALERT( M ) VerifyMessage( false, M )
	#else
	#define MESSAGE( M ) // do nothing
	#endif
}