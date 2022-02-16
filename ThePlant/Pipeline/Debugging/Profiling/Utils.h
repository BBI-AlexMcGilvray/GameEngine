#pragma once

#include "Core/Debugging/Headers/Macros.h"
#include "Core/Debugging/Headers/Declarations.h"
#include "Core/Headers/Service.h"

#include "Pipeline/Debugging/Profiling/Profiler.h"

#define PROFILE_PUSH(X) \
    WITH_SERVICE(Application::Profiling::Profiler)( \
        service->Push(#X); \
    )

#define DEBUG_PROFILE_PUSH(X) \
    WITH_DEBUG_SERVICE(Application::Profiling::Profiler)( \
        service->Push(#X); \
    )

#define PROFILE_POP(X) \
    WITH_SERVICE(Application::Profiling::Profiler)( \
        service->Pop(#X); \
    )

#define DEBUG_PROFILE_POP(X) \
    WITH_DEBUG_SERVICE(Application::Profiling::Profiler)( \
        service->Pop(#X); \
    )

#define PROFILE(X)  \
    PROFILE_PUSH(X)   \
    X;  \
    PROFILE_POP(X)

#define DEBUG_PROFILE(X)  \
    DEBUG_PROFILE_PUSH(X)   \
    X;  \
    DEBUG_PROFILE_POP(X)

#define CLEAR_PROFILE() \
    WITH_SERVICE(Application::Profiling::Profiler)( \
        service->Clear(); \
    )

#define DEBUG_CLEAR_PROFILE() \
    WITH_DEBUG_SERVICE(Application::Profiling::Profiler)( \
        service->Clear(); \
    )