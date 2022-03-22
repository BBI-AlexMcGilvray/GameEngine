#pragma once

#include <cassert>
#include <cstdlib>
#include <iostream>
#include <string> 

#include "Core/Headers/Macros.h"
#include "Core/Debugging/Headers/Declarations.h"

namespace Core {
bool VerifyCondition(bool condition, std::string conditionString, std::string callInfo);

#if DEBUG

#define VERIFY_1(X) Core::VerifyCondition(X, TO_STRING(X), std::string(__FILE__) + " (Line: " + std::to_string(__LINE__) + "): ")
#define VERIFY_2(X, T) Core::VerifyCondition(X, T, std::string(__FILE__) + " (Line: " + std::to_string(__LINE__) + "): ")
#define VERIFY(...) VERIFY_X(VA_NUM_ARGS(__VA_ARGS__), __VA_ARGS__)
#define VERIFY_X(ARG_COUNT, ...) PRIMITIVE_CAT(VERIFY_, ARG_COUNT)(__VA_ARGS__)

#define DEBUG_ASSERT_1(X)\
  if (!Core::VerifyCondition(X, TO_STRING(X), std::string(__FILE__) + " (Line: " + std::to_string(__LINE__) + "): ")) {\
    assert(X);\
  }
#define DEBUG_ASSERT_2(X, T)\
  if (!Core::VerifyCondition(X, T, std::string(__FILE__) + " (Line: " + std::to_string(__LINE__) + "): ")) {\
    assert(X);\
  }
#define DEBUG_ASSERT(...) DEBUG_ASSERT_X(VA_NUM_ARGS(__VA_ARGS__), __VA_ARGS__)
#define DEBUG_ASSERT_X(ARG_COUNT, ...) PRIMITIVE_CAT(DEBUG_ASSERT_, ARG_COUNT)(__VA_ARGS__)

#else // !DEBUG

#define DEBUG_ASSERT(...)

#endif

#define ASSERT_1(X)\
  if (!Core::VerifyCondition(X, TO_STRING(X), std::string(__FILE__) + " (Line: " + std::to_string(__LINE__) + "): ")) {\
    assert(X);\
  }
#define ASSERT_2(X, T)\
  if (!Core::VerifyCondition(X, T, std::string(__FILE__) + " (Line: " + std::to_string(__LINE__) + "): ")) {\
    assert(X);\
  }
#define ASSERT(...) ASSERT_X(VA_NUM_ARGS(__VA_ARGS__), __VA_ARGS__)
#define ASSERT_X(ARG_COUNT, ...) PRIMITIVE_CAT(ASSERT_, ARG_COUNT)(__VA_ARGS__)

}// namespace Core