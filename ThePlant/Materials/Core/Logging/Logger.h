#pragma once

#include "ILogger.h"

#include <memory>
#include <mutex>
#include <vector>

#include "Core/Headers/PtrDefs.h"
#include "Core/Headers/Service.h"

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
  WITH_SERVICE(Logger)
  (
    service->ThrowException<E>(tag, std::string(message));
  )
}

template <typename E, typename MESSAGE>
void ThrowException(const char* tag, const MESSAGE& message)
{
  ThrowException<E>(std::string(tag), std::string(message));
}

template <typename E, typename ...Args>
void ThrowException(Args ...args)
{
  WITH_SERVICE(Logger)
  (
    service->ThrowException<E>(std::forward<Args>(args)...);
  )
}

bool AddImplementation(std::shared_ptr<ILogger> implementation);
void RemoveImplementation(std::shared_ptr<ILogger> implementation);

class Logger : public ILogger
{  
public:
  struct ServiceOnlyConstructionTag{};
  Logger(ServiceOnlyConstructionTag tag);

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
  std::mutex _implementationsMutex;
  std::vector<std::shared_ptr<ILogger>> _implementations;
};
}// namespace Logging
}//namespace Core
