#include "Logger.h"

#include <exception>

#if _DEBUG
  #include "Core/Debugging/Memory/MemoryTrackerUtils.h"
  #include "Core/Headers/PtrDefs.h"
  #include "Core/Logging/ConsoleLogger.h"
#endif

namespace Core {
namespace Logging {
void Log(const std::string& tag, const std::string& message)
{
  WITH_SERVICE(Logger)
  (
    service->Log(tag, message);
  )
}

void LogWarning(const std::string& tag, const std::string& message)
{
  WITH_SERVICE(Logger)
  (
    service->LogWarning(tag, message);
  )
}

void LogError(const std::string& tag, const std::string& message)
{
  WITH_SERVICE(Logger)
  (
    service->LogError(tag, message);
  )
}

void ThrowException(const std::string& tag, const std::string& message)
{
  WITH_SERVICE(Logger)
  (
    service->ThrowException(tag, message);
  )
}

bool AddImplementation(std::shared_ptr<ILogger> implementation)
{
  WITH_SERVICE(Logger)
  (
    return service->AddImplementation(implementation);
  )

  return false;
}

void RemoveImplementation(std::shared_ptr<ILogger> implementation)
{
  WITH_SERVICE(Logger)
  (
    service->RemoveImplementation(implementation);
  )
}

// member functions
Logger::Logger(ServiceOnlyConstructionTag tag)
{
#if _DEBUG
  SCOPED_MEMORY_CATEGORY("Logger");
  AddImplementation(Core::MakeShared<ConsoleLogger>());
#endif
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
  SCOPED_MEMORY_CATEGORY("Logger");
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
}// namespace Logging
}//namespace Core