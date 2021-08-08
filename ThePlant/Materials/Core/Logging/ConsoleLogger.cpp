#include "ConsoleLogger.h"

#include <iostream>

namespace Core {
namespace Logging {
void ConsoleLogger::Log(const std::string& tag, const std::string& message)
{
  _coutMutex.lock();
  {
    std::cout << "I: [" << tag << "] " << message << std::endl;
  }
  _coutMutex.unlock();
}

void ConsoleLogger::LogWarning(const std::string& tag, const std::string& message)
{
  _coutMutex.lock();
  {
    std::cout << "W: [" << tag << "] " << message << std::endl;
  }
  _coutMutex.unlock();
}

void ConsoleLogger::LogError(const std::string& tag, const std::string& message)
{
  _coutMutex.lock();
  {
    std::cout << "E: [" << tag << "] " << message << std::endl;
  }
  _coutMutex.unlock();
}
}// namespace Logging
}//namespace Core