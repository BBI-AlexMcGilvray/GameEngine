#pragma once

#include "Core/Debugging/Headers/Declarations.h"
#include <cassert>
#include <cstdlib>
#include <iostream>
#include <string>

namespace Core {
inline void Message(std::string message, std::string callInfo)
{
  std::cout << callInfo << message << std::endl;
}

inline bool VerifyCondition(bool condition, std::string conditionString, std::string callInfo)
{
  bool result = condition;

  if (GLOBAL_EXPLICIT && !result && conditionString != "") {
    Message(conditionString, callInfo);
  }

  return result;
}

inline bool VerifyMessage(bool condition, std::string message, std::string callInfo)
{
  return VerifyCondition(condition, message, callInfo);
}

// need Core:: to be used in non-Core namespaces (gives C3861 identifier not found error)
#if DEBUG
#define VERIFY(X) Core::VerifyCondition(X, #X, std::string(__FILE__) + " (" + std::to_string(__LINE__) + "): ")
#else
#define VERIFY(X)// do nothing if not debugging
#endif

#if DEBUG
#define ASSERT(X)   \
  if (!VERIFY(X)) { \
    assert(X);      \
  }
#else
#define ASSERT(X)// do nothing if not debugging
#endif

#if DEBUG
#define MESSAGE(X, M) Core::VerifyMessage(X, M, std::string(__FILE__) + " (" + std::to_string(__LINE__) + "): ")
#else
#define MESSAGE(X, M)// do nothing
#endif

#if DEBUG
#define ALERT(M) Core::Message(M, std::string(__FILE__) + " (" + std::to_string(__LINE__) + "): ")
#else
#define MESSAGE(M)// do nothing
#endif

#if DEBUG
#define LOG(L) Core::Message(L, std::string(__FILE__) + " (" + std::to_string(__LINE__) + "): ")
#else
#define LOG(L)// do nothing
#endif
}// namespace Core