#pragma once

#include <cstdlib>
#include <iostream>
#include <cassert>
#include <string>

#include "Declarations.h"

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

#if DEBUG
#define VERIFY( X ) VerifyCondition( X, true )
#else
#define VERIFY( X ) // do nothing if not debugging
#endif

#if DEBUG
#define MESSAGE( X, M ) (bool condition = VERIFY( X, false ); if (!condition) { Message( M ); })
#else
#define MESSAGE( M ) // do nothing
#endif