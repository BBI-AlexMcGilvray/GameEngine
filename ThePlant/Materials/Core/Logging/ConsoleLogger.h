#pragma once

#include "ILogger.h"
#include <mutex>

namespace Core {
namespace Logging {
class ConsoleLogger : public ILogger
{
public:
  void Log(const std::string& tag, const std::string& message) override;
  void LogWarning(const std::string& tag, const std::string& message) override;
  void LogError(const std::string& tag, const std::string& message) override;

private:
  std::mutex _coutMutex;
};
}// namespace Logging
}//namespace Core