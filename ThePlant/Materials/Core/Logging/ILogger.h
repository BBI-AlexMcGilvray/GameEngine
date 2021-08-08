#pragma once

#include <string>

namespace Core {
namespace Logging {
enum LogTypeEnum {
  Info,
  Warning,
  Error,
  Exception
};

class ILogger
{
public:
  virtual ~ILogger() = default;

  virtual void Log(const std::string& tag, const std::string& message) = 0;
  virtual void LogWarning(const std::string& tag, const std::string& message) = 0;
  virtual void LogError(const std::string& tag, const std::string& message) = 0;
};
}// namespace Logging
}//namespace Core