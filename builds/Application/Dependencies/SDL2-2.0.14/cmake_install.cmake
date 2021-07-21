# Install script for directory: D:/Coding/VisualStudios/Application/Application/Dependencies/SDL2-2.0.14

# Set the install prefix
if(NOT DEFINED CMAKE_INSTALL_PREFIX)
  set(CMAKE_INSTALL_PREFIX "C:/Program Files (x86)/application")
endif()
string(REGEX REPLACE "/$" "" CMAKE_INSTALL_PREFIX "${CMAKE_INSTALL_PREFIX}")

# Set the install configuration name.
if(NOT DEFINED CMAKE_INSTALL_CONFIG_NAME)
  if(BUILD_TYPE)
    string(REGEX REPLACE "^[^A-Za-z0-9_]+" ""
           CMAKE_INSTALL_CONFIG_NAME "${BUILD_TYPE}")
  else()
    set(CMAKE_INSTALL_CONFIG_NAME "Release")
  endif()
  message(STATUS "Install configuration: \"${CMAKE_INSTALL_CONFIG_NAME}\"")
endif()

# Set the component getting installed.
if(NOT CMAKE_INSTALL_COMPONENT)
  if(COMPONENT)
    message(STATUS "Install component: \"${COMPONENT}\"")
    set(CMAKE_INSTALL_COMPONENT "${COMPONENT}")
  else()
    set(CMAKE_INSTALL_COMPONENT)
  endif()
endif()

# Is this installation the result of a crosscompile?
if(NOT DEFINED CMAKE_CROSSCOMPILING)
  set(CMAKE_CROSSCOMPILING "FALSE")
endif()

if("x${CMAKE_INSTALL_COMPONENT}x" STREQUAL "xUnspecifiedx" OR NOT CMAKE_INSTALL_COMPONENT)
  if("${CMAKE_INSTALL_CONFIG_NAME}" MATCHES "^([Dd][Ee][Bb][Uu][Gg])$")
    file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/lib" TYPE STATIC_LIBRARY FILES "D:/Coding/VisualStudios/Application/builds/Application/Dependencies/SDL2-2.0.14/Debug/SDL2d.lib")
  elseif("${CMAKE_INSTALL_CONFIG_NAME}" MATCHES "^([Rr][Ee][Ll][Ee][Aa][Ss][Ee])$")
    file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/lib" TYPE STATIC_LIBRARY FILES "D:/Coding/VisualStudios/Application/builds/Application/Dependencies/SDL2-2.0.14/Release/SDL2.lib")
  elseif("${CMAKE_INSTALL_CONFIG_NAME}" MATCHES "^([Mm][Ii][Nn][Ss][Ii][Zz][Ee][Rr][Ee][Ll])$")
    file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/lib" TYPE STATIC_LIBRARY FILES "D:/Coding/VisualStudios/Application/builds/Application/Dependencies/SDL2-2.0.14/MinSizeRel/SDL2.lib")
  elseif("${CMAKE_INSTALL_CONFIG_NAME}" MATCHES "^([Rr][Ee][Ll][Ww][Ii][Tt][Hh][Dd][Ee][Bb][Ii][Nn][Ff][Oo])$")
    file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/lib" TYPE STATIC_LIBRARY FILES "D:/Coding/VisualStudios/Application/builds/Application/Dependencies/SDL2-2.0.14/RelWithDebInfo/SDL2.lib")
  endif()
endif()

if("x${CMAKE_INSTALL_COMPONENT}x" STREQUAL "xUnspecifiedx" OR NOT CMAKE_INSTALL_COMPONENT)
  if("${CMAKE_INSTALL_CONFIG_NAME}" MATCHES "^([Dd][Ee][Bb][Uu][Gg])$")
    file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/lib" TYPE STATIC_LIBRARY FILES "D:/Coding/VisualStudios/Application/builds/Application/Dependencies/SDL2-2.0.14/Debug/SDL2maind.lib")
  elseif("${CMAKE_INSTALL_CONFIG_NAME}" MATCHES "^([Rr][Ee][Ll][Ee][Aa][Ss][Ee])$")
    file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/lib" TYPE STATIC_LIBRARY FILES "D:/Coding/VisualStudios/Application/builds/Application/Dependencies/SDL2-2.0.14/Release/SDL2main.lib")
  elseif("${CMAKE_INSTALL_CONFIG_NAME}" MATCHES "^([Mm][Ii][Nn][Ss][Ii][Zz][Ee][Rr][Ee][Ll])$")
    file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/lib" TYPE STATIC_LIBRARY FILES "D:/Coding/VisualStudios/Application/builds/Application/Dependencies/SDL2-2.0.14/MinSizeRel/SDL2main.lib")
  elseif("${CMAKE_INSTALL_CONFIG_NAME}" MATCHES "^([Rr][Ee][Ll][Ww][Ii][Tt][Hh][Dd][Ee][Bb][Ii][Nn][Ff][Oo])$")
    file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/lib" TYPE STATIC_LIBRARY FILES "D:/Coding/VisualStudios/Application/builds/Application/Dependencies/SDL2-2.0.14/RelWithDebInfo/SDL2main.lib")
  endif()
endif()

if("x${CMAKE_INSTALL_COMPONENT}x" STREQUAL "xUnspecifiedx" OR NOT CMAKE_INSTALL_COMPONENT)
  if(EXISTS "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/cmake/SDL2Targets.cmake")
    file(DIFFERENT EXPORT_FILE_CHANGED FILES
         "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/cmake/SDL2Targets.cmake"
         "D:/Coding/VisualStudios/Application/builds/Application/Dependencies/SDL2-2.0.14/CMakeFiles/Export/cmake/SDL2Targets.cmake")
    if(EXPORT_FILE_CHANGED)
      file(GLOB OLD_CONFIG_FILES "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/cmake/SDL2Targets-*.cmake")
      if(OLD_CONFIG_FILES)
        message(STATUS "Old export file \"$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/cmake/SDL2Targets.cmake\" will be replaced.  Removing files [${OLD_CONFIG_FILES}].")
        file(REMOVE ${OLD_CONFIG_FILES})
      endif()
    endif()
  endif()
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/cmake" TYPE FILE FILES "D:/Coding/VisualStudios/Application/builds/Application/Dependencies/SDL2-2.0.14/CMakeFiles/Export/cmake/SDL2Targets.cmake")
  if("${CMAKE_INSTALL_CONFIG_NAME}" MATCHES "^([Dd][Ee][Bb][Uu][Gg])$")
    file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/cmake" TYPE FILE FILES "D:/Coding/VisualStudios/Application/builds/Application/Dependencies/SDL2-2.0.14/CMakeFiles/Export/cmake/SDL2Targets-debug.cmake")
  endif()
  if("${CMAKE_INSTALL_CONFIG_NAME}" MATCHES "^([Mm][Ii][Nn][Ss][Ii][Zz][Ee][Rr][Ee][Ll])$")
    file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/cmake" TYPE FILE FILES "D:/Coding/VisualStudios/Application/builds/Application/Dependencies/SDL2-2.0.14/CMakeFiles/Export/cmake/SDL2Targets-minsizerel.cmake")
  endif()
  if("${CMAKE_INSTALL_CONFIG_NAME}" MATCHES "^([Rr][Ee][Ll][Ww][Ii][Tt][Hh][Dd][Ee][Bb][Ii][Nn][Ff][Oo])$")
    file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/cmake" TYPE FILE FILES "D:/Coding/VisualStudios/Application/builds/Application/Dependencies/SDL2-2.0.14/CMakeFiles/Export/cmake/SDL2Targets-relwithdebinfo.cmake")
  endif()
  if("${CMAKE_INSTALL_CONFIG_NAME}" MATCHES "^([Rr][Ee][Ll][Ee][Aa][Ss][Ee])$")
    file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/cmake" TYPE FILE FILES "D:/Coding/VisualStudios/Application/builds/Application/Dependencies/SDL2-2.0.14/CMakeFiles/Export/cmake/SDL2Targets-release.cmake")
  endif()
endif()

if("x${CMAKE_INSTALL_COMPONENT}x" STREQUAL "xDevelx" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/cmake" TYPE FILE FILES
    "D:/Coding/VisualStudios/Application/Application/Dependencies/SDL2-2.0.14/SDL2Config.cmake"
    "D:/Coding/VisualStudios/Application/builds/SDL2ConfigVersion.cmake"
    )
endif()

if("x${CMAKE_INSTALL_COMPONENT}x" STREQUAL "xUnspecifiedx" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/include/SDL2" TYPE FILE FILES
    "D:/Coding/VisualStudios/Application/Application/Dependencies/SDL2-2.0.14/include/SDL.h"
    "D:/Coding/VisualStudios/Application/Application/Dependencies/SDL2-2.0.14/include/SDL_assert.h"
    "D:/Coding/VisualStudios/Application/Application/Dependencies/SDL2-2.0.14/include/SDL_atomic.h"
    "D:/Coding/VisualStudios/Application/Application/Dependencies/SDL2-2.0.14/include/SDL_audio.h"
    "D:/Coding/VisualStudios/Application/Application/Dependencies/SDL2-2.0.14/include/SDL_bits.h"
    "D:/Coding/VisualStudios/Application/Application/Dependencies/SDL2-2.0.14/include/SDL_blendmode.h"
    "D:/Coding/VisualStudios/Application/Application/Dependencies/SDL2-2.0.14/include/SDL_clipboard.h"
    "D:/Coding/VisualStudios/Application/Application/Dependencies/SDL2-2.0.14/include/SDL_config_android.h"
    "D:/Coding/VisualStudios/Application/Application/Dependencies/SDL2-2.0.14/include/SDL_config_iphoneos.h"
    "D:/Coding/VisualStudios/Application/Application/Dependencies/SDL2-2.0.14/include/SDL_config_macosx.h"
    "D:/Coding/VisualStudios/Application/Application/Dependencies/SDL2-2.0.14/include/SDL_config_minimal.h"
    "D:/Coding/VisualStudios/Application/Application/Dependencies/SDL2-2.0.14/include/SDL_config_os2.h"
    "D:/Coding/VisualStudios/Application/Application/Dependencies/SDL2-2.0.14/include/SDL_config_pandora.h"
    "D:/Coding/VisualStudios/Application/Application/Dependencies/SDL2-2.0.14/include/SDL_config_psp.h"
    "D:/Coding/VisualStudios/Application/Application/Dependencies/SDL2-2.0.14/include/SDL_config_windows.h"
    "D:/Coding/VisualStudios/Application/Application/Dependencies/SDL2-2.0.14/include/SDL_config_winrt.h"
    "D:/Coding/VisualStudios/Application/Application/Dependencies/SDL2-2.0.14/include/SDL_config_wiz.h"
    "D:/Coding/VisualStudios/Application/Application/Dependencies/SDL2-2.0.14/include/SDL_copying.h"
    "D:/Coding/VisualStudios/Application/Application/Dependencies/SDL2-2.0.14/include/SDL_cpuinfo.h"
    "D:/Coding/VisualStudios/Application/Application/Dependencies/SDL2-2.0.14/include/SDL_egl.h"
    "D:/Coding/VisualStudios/Application/Application/Dependencies/SDL2-2.0.14/include/SDL_endian.h"
    "D:/Coding/VisualStudios/Application/Application/Dependencies/SDL2-2.0.14/include/SDL_error.h"
    "D:/Coding/VisualStudios/Application/Application/Dependencies/SDL2-2.0.14/include/SDL_events.h"
    "D:/Coding/VisualStudios/Application/Application/Dependencies/SDL2-2.0.14/include/SDL_filesystem.h"
    "D:/Coding/VisualStudios/Application/Application/Dependencies/SDL2-2.0.14/include/SDL_gamecontroller.h"
    "D:/Coding/VisualStudios/Application/Application/Dependencies/SDL2-2.0.14/include/SDL_gesture.h"
    "D:/Coding/VisualStudios/Application/Application/Dependencies/SDL2-2.0.14/include/SDL_haptic.h"
    "D:/Coding/VisualStudios/Application/Application/Dependencies/SDL2-2.0.14/include/SDL_hints.h"
    "D:/Coding/VisualStudios/Application/Application/Dependencies/SDL2-2.0.14/include/SDL_joystick.h"
    "D:/Coding/VisualStudios/Application/Application/Dependencies/SDL2-2.0.14/include/SDL_keyboard.h"
    "D:/Coding/VisualStudios/Application/Application/Dependencies/SDL2-2.0.14/include/SDL_keycode.h"
    "D:/Coding/VisualStudios/Application/Application/Dependencies/SDL2-2.0.14/include/SDL_loadso.h"
    "D:/Coding/VisualStudios/Application/Application/Dependencies/SDL2-2.0.14/include/SDL_locale.h"
    "D:/Coding/VisualStudios/Application/Application/Dependencies/SDL2-2.0.14/include/SDL_log.h"
    "D:/Coding/VisualStudios/Application/Application/Dependencies/SDL2-2.0.14/include/SDL_main.h"
    "D:/Coding/VisualStudios/Application/Application/Dependencies/SDL2-2.0.14/include/SDL_messagebox.h"
    "D:/Coding/VisualStudios/Application/Application/Dependencies/SDL2-2.0.14/include/SDL_metal.h"
    "D:/Coding/VisualStudios/Application/Application/Dependencies/SDL2-2.0.14/include/SDL_misc.h"
    "D:/Coding/VisualStudios/Application/Application/Dependencies/SDL2-2.0.14/include/SDL_mouse.h"
    "D:/Coding/VisualStudios/Application/Application/Dependencies/SDL2-2.0.14/include/SDL_mutex.h"
    "D:/Coding/VisualStudios/Application/Application/Dependencies/SDL2-2.0.14/include/SDL_name.h"
    "D:/Coding/VisualStudios/Application/Application/Dependencies/SDL2-2.0.14/include/SDL_opengl.h"
    "D:/Coding/VisualStudios/Application/Application/Dependencies/SDL2-2.0.14/include/SDL_opengl_glext.h"
    "D:/Coding/VisualStudios/Application/Application/Dependencies/SDL2-2.0.14/include/SDL_opengles.h"
    "D:/Coding/VisualStudios/Application/Application/Dependencies/SDL2-2.0.14/include/SDL_opengles2.h"
    "D:/Coding/VisualStudios/Application/Application/Dependencies/SDL2-2.0.14/include/SDL_opengles2_gl2.h"
    "D:/Coding/VisualStudios/Application/Application/Dependencies/SDL2-2.0.14/include/SDL_opengles2_gl2ext.h"
    "D:/Coding/VisualStudios/Application/Application/Dependencies/SDL2-2.0.14/include/SDL_opengles2_gl2platform.h"
    "D:/Coding/VisualStudios/Application/Application/Dependencies/SDL2-2.0.14/include/SDL_opengles2_khrplatform.h"
    "D:/Coding/VisualStudios/Application/Application/Dependencies/SDL2-2.0.14/include/SDL_pixels.h"
    "D:/Coding/VisualStudios/Application/Application/Dependencies/SDL2-2.0.14/include/SDL_platform.h"
    "D:/Coding/VisualStudios/Application/Application/Dependencies/SDL2-2.0.14/include/SDL_power.h"
    "D:/Coding/VisualStudios/Application/Application/Dependencies/SDL2-2.0.14/include/SDL_quit.h"
    "D:/Coding/VisualStudios/Application/Application/Dependencies/SDL2-2.0.14/include/SDL_rect.h"
    "D:/Coding/VisualStudios/Application/Application/Dependencies/SDL2-2.0.14/include/SDL_render.h"
    "D:/Coding/VisualStudios/Application/Application/Dependencies/SDL2-2.0.14/include/SDL_revision.h"
    "D:/Coding/VisualStudios/Application/Application/Dependencies/SDL2-2.0.14/include/SDL_rwops.h"
    "D:/Coding/VisualStudios/Application/Application/Dependencies/SDL2-2.0.14/include/SDL_scancode.h"
    "D:/Coding/VisualStudios/Application/Application/Dependencies/SDL2-2.0.14/include/SDL_sensor.h"
    "D:/Coding/VisualStudios/Application/Application/Dependencies/SDL2-2.0.14/include/SDL_shape.h"
    "D:/Coding/VisualStudios/Application/Application/Dependencies/SDL2-2.0.14/include/SDL_stdinc.h"
    "D:/Coding/VisualStudios/Application/Application/Dependencies/SDL2-2.0.14/include/SDL_surface.h"
    "D:/Coding/VisualStudios/Application/Application/Dependencies/SDL2-2.0.14/include/SDL_system.h"
    "D:/Coding/VisualStudios/Application/Application/Dependencies/SDL2-2.0.14/include/SDL_syswm.h"
    "D:/Coding/VisualStudios/Application/Application/Dependencies/SDL2-2.0.14/include/SDL_test.h"
    "D:/Coding/VisualStudios/Application/Application/Dependencies/SDL2-2.0.14/include/SDL_test_assert.h"
    "D:/Coding/VisualStudios/Application/Application/Dependencies/SDL2-2.0.14/include/SDL_test_common.h"
    "D:/Coding/VisualStudios/Application/Application/Dependencies/SDL2-2.0.14/include/SDL_test_compare.h"
    "D:/Coding/VisualStudios/Application/Application/Dependencies/SDL2-2.0.14/include/SDL_test_crc32.h"
    "D:/Coding/VisualStudios/Application/Application/Dependencies/SDL2-2.0.14/include/SDL_test_font.h"
    "D:/Coding/VisualStudios/Application/Application/Dependencies/SDL2-2.0.14/include/SDL_test_fuzzer.h"
    "D:/Coding/VisualStudios/Application/Application/Dependencies/SDL2-2.0.14/include/SDL_test_harness.h"
    "D:/Coding/VisualStudios/Application/Application/Dependencies/SDL2-2.0.14/include/SDL_test_images.h"
    "D:/Coding/VisualStudios/Application/Application/Dependencies/SDL2-2.0.14/include/SDL_test_log.h"
    "D:/Coding/VisualStudios/Application/Application/Dependencies/SDL2-2.0.14/include/SDL_test_md5.h"
    "D:/Coding/VisualStudios/Application/Application/Dependencies/SDL2-2.0.14/include/SDL_test_memory.h"
    "D:/Coding/VisualStudios/Application/Application/Dependencies/SDL2-2.0.14/include/SDL_test_random.h"
    "D:/Coding/VisualStudios/Application/Application/Dependencies/SDL2-2.0.14/include/SDL_thread.h"
    "D:/Coding/VisualStudios/Application/Application/Dependencies/SDL2-2.0.14/include/SDL_timer.h"
    "D:/Coding/VisualStudios/Application/Application/Dependencies/SDL2-2.0.14/include/SDL_touch.h"
    "D:/Coding/VisualStudios/Application/Application/Dependencies/SDL2-2.0.14/include/SDL_types.h"
    "D:/Coding/VisualStudios/Application/Application/Dependencies/SDL2-2.0.14/include/SDL_version.h"
    "D:/Coding/VisualStudios/Application/Application/Dependencies/SDL2-2.0.14/include/SDL_video.h"
    "D:/Coding/VisualStudios/Application/Application/Dependencies/SDL2-2.0.14/include/SDL_vulkan.h"
    "D:/Coding/VisualStudios/Application/Application/Dependencies/SDL2-2.0.14/include/begin_code.h"
    "D:/Coding/VisualStudios/Application/Application/Dependencies/SDL2-2.0.14/include/close_code.h"
    "D:/Coding/VisualStudios/Application/builds/Application/Dependencies/SDL2-2.0.14/include/SDL_config.h"
    )
endif()

