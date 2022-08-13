# Install script for directory: D:/Coding/VisualStudios/Application/ThePlant/Materials/Data

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
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/Data_Lib" TYPE FILE FILES
    "D:/Coding/VisualStudios/Application/ThePlant/Materials/Data/AssetTypes/EntityData.h"
    "D:/Coding/VisualStudios/Application/ThePlant/Materials/Data/AssetTypes/StateData.h"
    "D:/Coding/VisualStudios/Application/ThePlant/Materials/Data/Headers/AssetData.h"
    "D:/Coding/VisualStudios/Application/ThePlant/Materials/Data/Headers/AssetExceptions.h"
    "D:/Coding/VisualStudios/Application/ThePlant/Materials/Data/Headers/AssetLocation.h"
    "D:/Coding/VisualStudios/Application/ThePlant/Materials/Data/Headers/AssetLocationMapping.h"
    "D:/Coding/VisualStudios/Application/ThePlant/Materials/Data/Headers/AssetMacros.h"
    "D:/Coding/VisualStudios/Application/ThePlant/Materials/Data/Headers/AssetManager.h"
    "D:/Coding/VisualStudios/Application/ThePlant/Materials/Data/Headers/AssetName.h"
    "D:/Coding/VisualStudios/Application/ThePlant/Materials/Data/Headers/AssetType.h"
    "D:/Coding/VisualStudios/Application/ThePlant/Materials/Data/Headers/SerializationUtils.h"
    "D:/Coding/VisualStudios/Application/ThePlant/Materials/Data/RawAssets/RawAsset.h"
    "D:/Coding/VisualStudios/Application/ThePlant/Materials/Data/RawAssets/ReadUtils.h"
    "D:/Coding/VisualStudios/Application/ThePlant/Materials/Data/RawAssets/Utils.h"
    "D:/Coding/VisualStudios/Application/ThePlant/Materials/Data/RawAssets/WriteUtils.h"
    "D:/Coding/VisualStudios/Application/ThePlant/Materials/Data/Rendering/Headers/AnimatedMeshData.h"
    "D:/Coding/VisualStudios/Application/ThePlant/Materials/Data/Rendering/Headers/AnimatedModelData.h"
    "D:/Coding/VisualStudios/Application/ThePlant/Materials/Data/Rendering/Headers/MaterialData.h"
    "D:/Coding/VisualStudios/Application/ThePlant/Materials/Data/Rendering/Headers/SimpleMeshData.h"
    "D:/Coding/VisualStudios/Application/ThePlant/Materials/Data/Rendering/Headers/SimpleModelData.h"
    "D:/Coding/VisualStudios/Application/ThePlant/Materials/Data/Rendering/Headers/SkeletonAnimationData.h"
    "D:/Coding/VisualStudios/Application/ThePlant/Materials/Data/Rendering/Headers/SkeletonData.h"
    "D:/Coding/VisualStudios/Application/ThePlant/Materials/Data/Rendering/Headers/StaticMeshData.h"
    "D:/Coding/VisualStudios/Application/ThePlant/Materials/Data/Rendering/Headers/StaticModelData.h"
    "D:/Coding/VisualStudios/Application/ThePlant/Materials/Data/Rendering/Headers/TextureData.h"
    )
endif()

