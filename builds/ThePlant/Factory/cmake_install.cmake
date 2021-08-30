# Install script for directory: D:/Coding/VisualStudios/Application/ThePlant/Factory

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
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/Factory_Lib" TYPE FILE FILES
    "D:/Coding/VisualStudios/Application/ThePlant/Factory/CustomData/Headers/DataCreation.h"
    "D:/Coding/VisualStudios/Application/ThePlant/Factory/CustomData/Headers/DataExportDefs.h"
    "D:/Coding/VisualStudios/Application/ThePlant/Factory/CustomData/Headers/DataExportUtils.h"
    "D:/Coding/VisualStudios/Application/ThePlant/Factory/Headers/ExportData.h"
    "D:/Coding/VisualStudios/Application/ThePlant/Factory/Headers/ExportException.h"
    "D:/Coding/VisualStudios/Application/ThePlant/Factory/Rendering/Headers/AssimpExtensions.h"
    "D:/Coding/VisualStudios/Application/ThePlant/Factory/Rendering/Headers/MaterialExport.h"
    "D:/Coding/VisualStudios/Application/ThePlant/Factory/Rendering/Headers/MeshExport.h"
    "D:/Coding/VisualStudios/Application/ThePlant/Factory/Rendering/Headers/ModelExport.h"
    "D:/Coding/VisualStudios/Application/ThePlant/Factory/Rendering/Headers/SceneConversion.h"
    "D:/Coding/VisualStudios/Application/ThePlant/Factory/Rendering/Headers/SkeletonAnimationExport.h"
    "D:/Coding/VisualStudios/Application/ThePlant/Factory/Rendering/Headers/SkeletonExport.h"
    "D:/Coding/VisualStudios/Application/ThePlant/Factory/Rendering/Headers/TextureExport.h"
    "D:/Coding/VisualStudios/Application/ThePlant/Factory/Rendering/Headers/Utils.h"
    "D:/Coding/VisualStudios/Application/ThePlant/Factory/SQL/Headers/SQLDefs.h"
    "D:/Coding/VisualStudios/Application/ThePlant/Factory/SQL/Headers/SQLExceptions.h"
    "D:/Coding/VisualStudios/Application/ThePlant/Factory/SQL/Headers/SQLInstance.h"
    )
endif()

if(NOT CMAKE_INSTALL_LOCAL_ONLY)
  # Include the install script for each subdirectory.
  include("D:/Coding/VisualStudios/Application/builds/ThePlant/Factory/Workers/cmake_install.cmake")

endif()

