# Set a default build type if none was specified
if(NOT CMAKE_BUILD_TYPE AND NOT CMAKE_CONFIGURATION_TYPES)
  message(STATUS "Setting build type to 'Debug' as none was specified.")
  set(CMAKE_BUILD_TYPE
      Debug
      CACHE STRING "Choose the type of build." FORCE)
  # Set the possible values of build type for cmake-gui, ccmake
  set_property(
    CACHE CMAKE_BUILD_TYPE
    PROPERTY STRINGS
             "Debug"
             "Release"
             "MinSizeRelease"
             "ReleaseWithDebugInfo")
endif()

# Generate compile_commands.json to make it easier to work with clang based tools
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

# trying to get rid of lnk4217 errors (https://stackoverflow.com/questions/14172856/compile-with-mt-instead-of-md-using-cmake)
# if change, rerun 'cmake .' before Building
# issue may be the lack of settings extending to sdl and glew?
# other options...
#   - https://cmake.org/cmake/help/v3.19/prop_tgt/MSVC_RUNTIME_LIBRARY.html
#set(CMAKE_CXX_FLAGS "/MT")
#set(CMAKE_CXX_FLAGS_DEBUG "/MT")
#set(CMAKE_CXX_FLAGS_RELEASE "/MT")
#set(CMAKE_C_FLAGS "/MT")
#set(CMAKE_C_FLAGS_DEBUG "/MT")
#set(CMAKE_C_FLAGS_RELEASE "/MT")

option(ENABLE_IPO "Enable Interprocedural Optimization, aka Link Time Optimization (LTO)" OFF)

if(ENABLE_IPO)
  include(CheckIPOSupported)
  check_ipo_supported(
    RESULT
    result
    OUTPUT
    output)
  if(result)
    set(CMAKE_INTERPROCEDURAL_OPTIMIZATION TRUE)
  else()
    message(SEND_ERROR "IPO is not supported: ${output}")
  endif()
endif()
if(CMAKE_CXX_COMPILER_ID MATCHES ".*Clang")
  add_compile_options(-fcolor-diagnostics)
elseif(CMAKE_CXX_COMPILER_ID STREQUAL "GNU")
  add_compile_options(-fdiagnostics-color=always)
else()
  message(STATUS "No colored compiler diagnostic set for '${CMAKE_CXX_COMPILER_ID}' compiler.")
endif()
