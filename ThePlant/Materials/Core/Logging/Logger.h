#pragma once

#include "ILogger.h"
#include <memory>
#include <mutex>
#include <vector>

namespace Core {
namespace Logging {
// do not call this directly, use the macros
void Log(const std::string& tag, const std::string& message);
void LogWarning(const std::string& tag, const std::string& message);
void LogError(const std::string& tag, const std::string& message);
void ThrowException(const std::string& tag, const std::string& message);

template <typename E>
void ThrowException(const std::string& tag, const std::string& message)
{
  Logger::Instance->ThrowException<T>(tag, message);
}

template <typename E, typename ...Args>
void ThrowException(Args... args)
{
  Logger::Instance->ThrowException<T>(std::forward<Args>(args)...);
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
    throw E("[" + tag + "] " + message);
  }

  template <typename E, typename ...Args>
  void ThrowException(Args... args)
  {
    throw E(std::forward<Args>(args)...);
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

#if _DEBUG

#define DEBUG_LOG(tag, message) Logging::Log(tag, message)
#define DEBUG_WARNING(tag, message) Logging::LogWarning(tag, message)
#define DEBUG_ERROR(tag, message) Logging::LogError(tag, message)
// the DEBUG_THROW macro will need to forward to other macros based on arguments
#define DEBUG_THROW(tag, message) Logging::ThrowException(tag, message)
#define DEBUG_THROW(type, tag, message) Logging::ThrowException<type>(tag, message)
#define DEBUG_THROW(type, A) Logging::ThrowException<type>(A)
#define DEBUG_THROW(type, A, B, C, ...) Logging::ThrowException<type>(A, B, C, __VA_ARGS__)

#else // !_DEBUG

#define DEBUG_LOG(tag, message)
#define DEBUG_WARNING(tag, message)
#define DEBUG_ERROR(tag, message)
// the DEBUG_THROW macro will need to forward to other macros based on arguments
#define DEBUG_THROW(tag, message)
#define DEBUG_THROW(type, tag, message)
#define DEBUG_THROW(type, A)
#define DEBUG_THROW(type, A, B, C, ...)

#endif

#define LOG(tag, message) Logging::Log(tag, message)
#define WARNING(tag, message) Logging::LogWarning(tag, message)
#define ERROR(tag, message) Logging::LogError(tag, message)
// the THROW macro will need to forward to other macros based on arguments
#define THROW(tag, message) Logging::ThrowException(tag, message)
#define THROW(type, tag, message) Logging::ThrowException<type>(tag, message)
#define THROW(type, A) Logging::ThrowException<type>(A)
#define THROW(type, A, B, C, ...) Logging::ThrowException<type>(A, B, C, __VA_ARGS__)