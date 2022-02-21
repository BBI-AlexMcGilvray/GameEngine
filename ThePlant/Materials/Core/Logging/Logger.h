#pragma once

#include "ILogger.h"

#include <memory>
#include <mutex>
#include <vector>

#include "Core/Headers/PtrDefs.h"

namespace Core {
namespace Logging {
// do not call this directly, use the macros
void Log(const std::string& tag, const std::string& message);
void LogWarning(const std::string& tag, const std::string& message);
void LogError(const std::string& tag, const std::string& message);
void ThrowException(const std::string& tag, const std::string& message);

// not pretty, ideally we would handle things on a more case-by-case basis, but we want to catch any instance of being given a (TAG, message) pair
// without having to specify them all, so assume TAG is also std::string or const char* and from there assume we are being given a 'message' as the next parameter
template <typename E, typename MESSAGE>
void ThrowException(const std::string& tag, const MESSAGE& message)
{
  Logger::Instance()->ThrowException<E>(tag, std::string(message));
}

template <typename E, typename MESSAGE>
void ThrowException(const char* tag, const MESSAGE& message)
{
  ThrowException<E>(std::string(tag), std::string(message));
}

template <typename E, typename ...Args>
void ThrowException(Args ...args)
{
  Logger::Instance()->ThrowException<E>(std::forward<Args>(args)...);
}

bool AddImplementation(std::shared_ptr<ILogger> implementation);
void RemoveImplementation(std::shared_ptr<ILogger> implementation);

class Logger : public ILogger
{
private: 
  struct ConstructorTag{};
  
public:
  static Logger *Instance();

  Logger(ConstructorTag tag);

  void Log(const std::string& tag, const std::string& message) override;
  void LogWarning(const std::string& tag, const std::string& message) override;
  void LogError(const std::string& tag, const std::string& message) override;

  void ThrowException(const std::string& tag, const std::string& message);

  template <typename E>
  void ThrowException(const std::string& tag, const std::string& message)
  {
    throw E(std::string("[" + tag + "] " + message));
  }

  template <typename E, typename ...Args>
  void ThrowException(Args... args)
  {
    throw E(args...);
  }

  bool AddImplementation(std::shared_ptr<ILogger> implementation);
  void RemoveImplementation(std::shared_ptr<ILogger> implementation);

private:
  static std::unique_ptr<Logger> _instance;

  std::mutex _implementationsMutex;
  std::vector<std::shared_ptr<ILogger>> _implementations;
};
}// namespace Logging
}//namespace Core

#if DEBUG

#define DEBUG_LOG(tag, message) Core::Logging::Log(tag, message)
#define DEBUG_WARNING(tag, message) Core::Logging::LogWarning(tag, message)
#define DEBUG_ERROR(tag, message) Core::Logging::LogError(tag, message)
#define DEBUG_THROW(tag, message) Core::Logging::ThrowException(tag, message); throw
#define DEBUG_THROW_EXCEPTION(type, ...) Core::Logging::ThrowException<type>(__VA_ARGS__); throw

#else // !DEBUG

#define DEBUG_LOG(tag, message)
#define DEBUG_WARNING(tag, message)
#define DEBUG_ERROR(tag, message)
#define DEBUG_THROW(tag, message) 
#define DEBUG_THROW_EXCEPTION(type, ...)

#endif

#define CORE_LOG(tag, message) Core::Logging::Log(tag, message)
#define CORE_WARNING(tag, message) Core::Logging::LogWarning(tag, message)
#define CORE_ERROR(tag, message) Core::Logging::LogError(tag, message)
#define CORE_THROW(tag, message) Core::Logging::ThrowException(tag, message); throw
#define CORE_THROW_EXCEPTION(type, ...) Core::Logging::ThrowException<type>(__VA_ARGS__); throw