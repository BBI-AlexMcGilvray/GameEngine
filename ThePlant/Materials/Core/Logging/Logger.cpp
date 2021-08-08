#include "Logger.h"

#include <exception>

#if _DEBUG
  #include "Core/Headers/PtrDefs.h"
  #include "Core/Logging/ConsoleLogger.h"
#endif

namespace Core {
namespace Logging {
void Log(const std::string& tag, const std::string& message) { Logger::Instance()->Log(tag, message); }
void LogWarning(const std::string& tag, const std::string& message) { Logger::Instance()->LogWarning(tag, message); }
void LogError(const std::string& tag, const std::string& message) { Logger::Instance()->LogError(tag, message); }
void ThrowException(const std::string& tag, const std::string& message) { Logger::Instance()->ThrowException(tag, message); }

bool AddImplementation(std::shared_ptr<ILogger> implementation) { return Logger::Instance()->AddImplementation(implementation); }
void RemoveImplementation(std::shared_ptr<ILogger> implementation) { Logger::Instance()->RemoveImplementation(implementation); }

// member functinos
std::unique_ptr<Logger> Logger::_instance = nullptr;

Logger *Logger::Instance()
{
  if (_instance.get() == nullptr) {
    _instance = std::make_unique<Logger>(ConstructorTag{});
  }

  return _instance.get();
}

void Logger::Log(const std::string& tag, const std::string& message)
{
  _implementationsMutex.lock();
  {
    for (int i = 0; i < _implementations.size(); i++) {
      _implementations[i]->Log(tag, message);
    }
  }
  _implementationsMutex.unlock();
}

void Logger::LogWarning(const std::string& tag, const std::string& message)
{
  _implementationsMutex.lock();
  {
    for (int i = 0; i < _implementations.size(); i++) {
      _implementations[i]->LogWarning(tag, message);
    }
  }
  _implementationsMutex.unlock();
}

void Logger::LogError(const std::string& tag, const std::string& message)
{
  _implementationsMutex.lock();
  {
    for (int i = 0; i < _implementations.size(); i++) {
      _implementations[i]->LogError(tag, message);
    }
  }
  _implementationsMutex.unlock();
}

void Logger::ThrowException(const std::string& tag, const std::string& message)
{
  throw std::runtime_error("[" + tag + "] " + message);
}

bool Logger::AddImplementation(std::shared_ptr<ILogger> implementation)
{
  bool add = true;
  _implementationsMutex.lock();
  {
    for (int i = 0; i < _implementations.size(); i++) {
      if (_implementations[i] == implementation) {
        add = false;
      }
    }

    if (add) {
      _implementations.push_back(implementation);
    }
  }
  _implementationsMutex.unlock();

  return add;
}

void Logger::RemoveImplementation(std::shared_ptr<ILogger> implementation)
{
  _implementationsMutex.lock();
  {
    for (int i = 0; i < _implementations.size(); i++) {
      if (_implementations[i] == implementation) {
        _implementations.erase(_implementations.begin() + i);
        return;
      }
    }
  }
  _implementationsMutex.unlock();
}

Logger::Logger(ConstructorTag tag)
{
#if _DEBUG
  AddImplementation(Core::MakeShared<ConsoleLogger>());
#endif
}
}// namespace Logging
}//namespace Core