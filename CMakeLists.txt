cmake_minimum_required(VERSION 3.12.2)
set(CMAKE_GENERATOR "Visual Studio 16 2019")

# how the fuck do you set optimization levels?
# set(CMAKE_CXX_FLAGS_RELEASE       "-O3 -DNDEBUG"            CACHE STRING "c++ Debug flags" )
# set(CMAKE_C_FLAGS_RELEASE         "-O3 -DNDEBUG"            CACHE STRING "c Debug flags" )
# set(CMAKE_CXX_FLAGS_DEBUG       "-O3 -DNDEBUG"            CACHE STRING "c++ Release flags" )
# set(CMAKE_C_FLAGS_DEBUG         "-O3 -DNDEBUG"            CACHE STRING "c Release flags" )
set(CMAKE_CXX_FLAGS       "-fembed-bitcode -O3"            CACHE STRING "c++ Debug flags" )
set(CMAKE_C_FLAGS         "-fembed-bitcode -O3"            CACHE STRING "c Debug flags" )

# Set the project name to the_plant
project(the_plant VERSION 1.0.0 LANGUAGES CXX)
include(cmake/ProjectSettings.cmake)
include(cmake/PreventInSourceBuilds.cmake)

# Link this 'library' to set the c++ standard / compile-time options requested
add_library(build_options INTERFACE)
target_compile_features(build_options INTERFACE cxx_std_17)

# Visual Studio's compiler needs to be told to 'act correctly' (act according to the standard)
add_compile_options(/std:c++17)
add_compile_options(/std:c17)
add_compile_options(/Zc:preprocessor)

if(CMAKE_CXX_COMPILER_ID MATCHES ".*Clang")
  option(ENABLE_BUILD_WITH_TIME_TRACE "Enable -ftime-trace to generate time tracing .json files on clang" OFF)
  if(ENABLE_BUILD_WITH_TIME_TRACE)
    target_compile_options(build_options INTERFACE -ftime-trace)
  endif()
endif() 

# Link this 'library' to use the warnings specified in CompilerWarnings.cmake
add_library(build_warnings INTERFACE)

# enable cache system
include(cmake/Cache.cmake)

# TURN ON ONCE CODE IS CLEANED UP
# standard compiler warnings
#include(cmake/CompilerWarnings.cmake)
#set_project_warnings(build_warnings)

# TURN ON ONCE CODE IS CLEANED UP
# sanitizer options if supported by compiler
#include(cmake/Sanitizers.cmake)
#enable_sanitizers(build_options)

# TURN ON ONCE CODE IS CLEANED UP
# allow for static analysis options
#include(cmake/StaticAnalyzers.cmake)

option(BUILD_SHARED_LIBS "Enable compilation of shared libraries" OFF)
option(ENABLE_TESTING "Enable Test Builds" OFF)

# Very basic PCH example
option(ENABLE_PCH "Enable Precompiled Headers" OFF)
if(ENABLE_PCH)
  # This sets a global PCH parameter, each project will build its own PCH, which is a good idea if any #define's change
  #
  # consider breaking this out per project as necessary
  target_precompile_headers(
    build_options
    INTERFACE
    <vector>
    <string>
    <map>
    <utility>)
endif()

if(ENABLE_TESTING)
  enable_testing()
  message("Building Tests. Be sure to check out test/constexpr_tests for constexpr testing")
  add_subdirectory(test)
endif()

add_subdirectory(ThePlant)

option(ENABLE_UNITY "Enable Unity builds of projects" OFF)
if(ENABLE_UNITY)
  # Add for any project you want to apply unity builds for
  set_target_properties(intro PROPERTIES UNITY_BUILD ON)
endif()