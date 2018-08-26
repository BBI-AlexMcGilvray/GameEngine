#pragma once

#include <cstdlib>
#include <iostream>
#include <cassert>
#include <string>

#include "Declarations.h"

namespace Core
{
	inline void Message(std::string message, std::string callInfo)
	{
		std::cout << callInfo << message << std::endl;
	}

	inline bool VerifyCondition(bool condition, std::string conditionString, std::string callInfo)
	{
		bool result = condition;

		if (GLOBAL_EXPLICIT && !result && conditionString != "")
		{
			Message(conditionString, callInfo);
		}
		
		return result;
	}

	inline bool VerifyMessage(bool condition, std::string message, std::string callInfo)
	{
		return VerifyCondition(condition, message, callInfo);
	}

	#if DEBUG
#define VERIFY( X ) VerifyCondition( X, #X, std::string(__FILE__) + " (" + std::to_string(__LINE__) + "): " )
	#else
	#define VERIFY( X ) // do nothing if not debugging
	#endif

	#if DEBUG
	#define MESSAGE( X, M ) VerifyMessage( X, M, std::string(__FILE__) + " (" + std::to_string(__LINE__) + "): " )
	#else
	#define MESSAGE( X, M ) // do nothing
	#endif

	#if DEBUG
	#define ALERT( M ) Message( M, std::string(__FILE__) + " (" + std::to_string(__LINE__) + "): " )
	#else
	#define MESSAGE( M ) // do nothing
	#endif

	#if DEBUG
	#define LOG( L ) Message( L, std::string(__FILE__) + " (" + std::to_string(__LINE__) + "): " )
	#else
	#define LOG( L ) // do nothing
	#endif
}