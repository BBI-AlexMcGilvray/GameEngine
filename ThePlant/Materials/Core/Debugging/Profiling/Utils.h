#pragma once

#include "Core/Debugging/Headers/Macros.h"
#include "Core/Headers/Service.h"
#include "Core/Headers/Finally.h"

#include "Core/Debugging/Profiling/Profiler.h"

// ideally we find a way to ensure the below names are unique through some sort of incremental macro
#define PROFILE_SCOPE(X)    \
    Core::Finally scopedProfilerFinally;    \
    WITH_SERVICE(Core::Profiling::Profiler)( \
        service->Push(X);  \
        const std::string& scopedProfilerTag = X;   \
        scopedProfilerFinally = Core::Finally([service, scopedProfilerTag]() mutable   \
        {   \
            service->Pop(scopedProfilerTag);   \
        }); \
    )

#define DEBUG_PROFILE_SCOPE(X)  \
    Core::Finally scopedProfilerFinally;    \
    WITH_DEBUG_SERVICE(Core::Profiling::Profiler)( \
        service->Push(X);  \
        const std::string& scopedProfilerTag = X;   \
        scopedProfilerFinally = Core::Finally([service, scopedProfilerTag]() mutable   \
        {   \
            service->Pop(scopedProfilerTag);   \
        }); \
    )

#define PROFILE_PUSH(X) \
    WITH_SERVICE(Core::Profiling::Profiler)( \
        service->Push(X); \
    )

#define DEBUG_PROFILE_PUSH(X) \
    WITH_DEBUG_SERVICE(Core::Profiling::Profiler)( \
        service->Push(X); \
    )

#define PROFILE_POP(X) \
    WITH_SERVICE(Core::Profiling::Profiler)( \
        service->Pop(X); \
    )

#define DEBUG_PROFILE_POP(X) \
    WITH_DEBUG_SERVICE(Core::Profiling::Profiler)( \
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
    WITH_SERVICE(Core::Profiling::Profiler)( \
        service->ClearSections(); \
    )

#define DEBUG_CLEAR_PROFILE() \
    WITH_DEBUG_SERVICE(Core::Profiling::Profiler)( \
        service->ClearSections(); \
    )