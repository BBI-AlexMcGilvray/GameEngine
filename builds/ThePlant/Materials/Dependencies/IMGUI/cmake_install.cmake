# Install script for directory: D:/Coding/VisualStudios/Application/ThePlant/Materials/Dependencies/IMGUI

# Set the install prefix
if(NOT DEFINED CMAKE_INSTALL_PREFIX)
  set(CMAKE_INSTALL_PREFIX "C:/Program Files (x86)/the_plant")
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
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/IMGUI_Lib" TYPE FILE FILES
    "D:/Coding/VisualStudios/Application/ThePlant/Materials/Dependencies/IMGUI/imconfig.h"
    "D:/Coding/VisualStudios/Application/ThePlant/Materials/Dependencies/IMGUI/imgui_internal.h"
    "D:/Coding/VisualStudios/Application/ThePlant/Materials/Dependencies/IMGUI/imgui.h"
    "D:/Coding/VisualStudios/Application/ThePlant/Materials/Dependencies/IMGUI/imstb_rectpack.h"
    "D:/Coding/VisualStudios/Application/ThePlant/Materials/Dependencies/IMGUI/imstb_textecit.h"
    "D:/Coding/VisualStudios/Application/ThePlant/Materials/Dependencies/IMGUI/imstb_truetype.h"
    "D:/Coding/VisualStudios/Application/ThePlant/Materials/Dependencies/IMGUI/backends/imgui_impl_opengl3.h"
    "D:/Coding/VisualStudios/Application/ThePlant/Materials/Dependencies/IMGUI/backends/imgui_impl_sdl.h"
    )
endif()

