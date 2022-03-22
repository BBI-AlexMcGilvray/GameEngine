#include "Core/Debugging/Headers/Macros.h"
#include "Core/Logging/LogFunctions.h"

namespace Core {
bool VerifyCondition(bool condition, std::string conditionString, std::string callInfo)
{
  bool result = condition;

  if (GLOBAL_EXPLICIT && !result && conditionString != "") {
    CORE_LOG("VERIFYING", conditionString + "; " + callInfo);
  }

  return result;
}
} // namespace Core