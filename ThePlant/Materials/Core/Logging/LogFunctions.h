#include "Core/Logging/Logger.h"

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