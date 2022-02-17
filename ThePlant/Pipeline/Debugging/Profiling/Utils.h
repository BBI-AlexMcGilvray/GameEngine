#pragma once

#include "Core/Debugging/Headers/Macros.h"
#include "Core/Debugging/Headers/Declarations.h"
#include "Core/Headers/Service.h"
#include "Core/Headers/Finally.h"

#include "Pipeline/Debugging/Profiling/Profiler.h"

// ideally we find a way to ensure the below names are unique through some sort of incremental macro
#define PROFILE_SCOPE(X)    \
    Core::Finally scopedProfilerFinally;    \
    WITH_SERVICE(Application::Profiling::Profiler)( \
        service->Push(X);  \
        scopedProfilerFinally = Core::Finally([service]() mutable   \
        {   \
            service->Pop(X);   \
        }); \
    )

#define DEBUG_PROFILE_SCOPE(X)  \
    Core::Finally scopedProfilerFinally;    \
    WITH_DEBUG_SERVICE(Application::Profiling::Profiler)( \
        service->Push(X);  \
        scopedProfilerFinally = Core::Finally([service]() mutable   \
        {   \
            service->Pop(X);   \
        }); \
    )

#define PROFILE_PUSH(X) \
    WITH_SERVICE(Application::Profiling::Profiler)( \
        service->Push(X); \
    )

#define DEBUG_PROFILE_PUSH(X) \
    WITH_DEBUG_SERVICE(Application::Profiling::Profiler)( \
        service->Push(X); \
    )

#define PROFILE_POP(X) \
    WITH_SERVICE(Application::Profiling::Profiler)( \
        service->Pop(X); \
    )

#define DEBUG_PROFILE_POP(X) \
    WITH_DEBUG_SERVICE(Application::Profiling::Profiler)( \
        service->Pop(X); \
    )

#define PROFILE(X)  \
    PROFILE_PUSH(#X)   \
    X;  \
    PROFILE_POP(#X)

#define DEBUG_PROFILE(X)  \
    DEBUG_PROFILE_PUSH(#X)   \
    X;  \
    DEBUG_PROFILE_POP(#X)

#define CLEAR_PROFILE() \
    WITH_SERVICE(Application::Profiling::Profiler)( \
        service->Clear(); \
    )

#define DEBUG_CLEAR_PROFILE() \
    WITH_DEBUG_SERVICE(Application::Profiling::Profiler)( \
        service->Clear(); \
    )