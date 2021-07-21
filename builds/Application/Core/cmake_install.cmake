# Install script for directory: D:/Coding/VisualStudios/Application/Application/Core

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
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/Core" TYPE FILE FILES
    "D:/Coding/VisualStudios/Application/Application/Core/Debugging/Headers/Declarations.h"
    "D:/Coding/VisualStudios/Application/Application/Core/Debugging/Headers/Macros.h"
    "D:/Coding/VisualStudios/Application/Application/Core/Functionality/Headers/Event.h"
    "D:/Coding/VisualStudios/Application/Application/Core/Functionality/Headers/Function.h"
    "D:/Coding/VisualStudios/Application/Application/Core/Functionality/Headers/LockerBase.h"
    "D:/Coding/VisualStudios/Application/Application/Core/Functionality/Headers/Scheduler.h"
    "D:/Coding/VisualStudios/Application/Application/Core/Functionality/Headers/Subscription.h"
    "D:/Coding/VisualStudios/Application/Application/Core/Geometric/2D/Headers/Box.h"
    "D:/Coding/VisualStudios/Application/Application/Core/Geometric/2D/Headers/Circle.h"
    "D:/Coding/VisualStudios/Application/Application/Core/Geometric/2D/Headers/Geometry.h"
    "D:/Coding/VisualStudios/Application/Application/Core/Geometric/2D/Headers/GeometryFunctions.h"
    "D:/Coding/VisualStudios/Application/Application/Core/Geometric/2D/Headers/Line.h"
    "D:/Coding/VisualStudios/Application/Application/Core/Geometric/2D/Headers/Point.h"
    "D:/Coding/VisualStudios/Application/Application/Core/Geometric/2D/Headers/Polygon.h"
    "D:/Coding/VisualStudios/Application/Application/Core/Geometric/Headers/GeometryDefs.h"
    "D:/Coding/VisualStudios/Application/Application/Core/Geometric/Headers/Transform.h"
    "D:/Coding/VisualStudios/Application/Application/Core/Headers/AllCore.h"
    "D:/Coding/VisualStudios/Application/Application/Core/Headers/CoreDefs.h"
    "D:/Coding/VisualStudios/Application/Application/Core/Headers/Exception.h"
    "D:/Coding/VisualStudios/Application/Application/Core/Headers/FlagEnum.h"
    "D:/Coding/VisualStudios/Application/Application/Core/Headers/Hash.h"
    "D:/Coding/VisualStudios/Application/Application/Core/Headers/ListDefs.h"
    "D:/Coding/VisualStudios/Application/Application/Core/Headers/MapDefs.h"
    "D:/Coding/VisualStudios/Application/Application/Core/Headers/Property.h"
    "D:/Coding/VisualStudios/Application/Application/Core/Headers/PtrDefs.h"
    "D:/Coding/VisualStudios/Application/Application/Core/Headers/TemplateDefs.h"
    "D:/Coding/VisualStudios/Application/Application/Core/Headers/TimeDefs.h"
    "D:/Coding/VisualStudios/Application/Application/Core/IO/Headers/Exception.h"
    "D:/Coding/VisualStudios/Application/Application/Core/IO/Headers/File.h"
    "D:/Coding/VisualStudios/Application/Application/Core/IO/Headers/Folder.h"
    "D:/Coding/VisualStudios/Application/Application/Core/IO/Headers/IODefs.h"
    "D:/Coding/VisualStudios/Application/Application/Core/IO/Headers/IOUtils.h"
    "D:/Coding/VisualStudios/Application/Application/Core/Math/Headers/Axis.h"
    "D:/Coding/VisualStudios/Application/Application/Core/Math/Headers/Basis.h"
    "D:/Coding/VisualStudios/Application/Application/Core/Math/Headers/Color.h"
    "D:/Coding/VisualStudios/Application/Application/Core/Math/Headers/MathDefs.h"
    "D:/Coding/VisualStudios/Application/Application/Core/Math/Headers/MathUtils.h"
    "D:/Coding/VisualStudios/Application/Application/Core/Math/Headers/Matrix.h"
    "D:/Coding/VisualStudios/Application/Application/Core/Math/Headers/Matrix2x2.h"
    "D:/Coding/VisualStudios/Application/Application/Core/Math/Headers/Matrix3x3.h"
    "D:/Coding/VisualStudios/Application/Application/Core/Math/Headers/Matrix4x4.h"
    "D:/Coding/VisualStudios/Application/Application/Core/Math/Headers/MatrixFunctions.h"
    "D:/Coding/VisualStudios/Application/Application/Core/Math/Headers/Quaternion.h"
    "D:/Coding/VisualStudios/Application/Application/Core/Math/Headers/QuaternionFunctions.h"
    "D:/Coding/VisualStudios/Application/Application/Core/Math/Headers/UtilityFunctions.h"
    "D:/Coding/VisualStudios/Application/Application/Core/Math/Headers/Vector.h"
    "D:/Coding/VisualStudios/Application/Application/Core/Math/Headers/Vector2.h"
    "D:/Coding/VisualStudios/Application/Application/Core/Math/Headers/Vector3.h"
    "D:/Coding/VisualStudios/Application/Application/Core/Math/Headers/Vector4.h"
    "D:/Coding/VisualStudios/Application/Application/Core/Math/Headers/VectorFunctions.h"
    "D:/Coding/VisualStudios/Application/Application/Core/Math/UnitTests/MathUnitTests.h"
    "D:/Coding/VisualStudios/Application/Application/Core/Math/UnitTests/MatrixTests.h"
    "D:/Coding/VisualStudios/Application/Application/Core/Math/UnitTests/VectorTests.h"
    "D:/Coding/VisualStudios/Application/Application/Core/Networking/Headers/Macros.h"
    "D:/Coding/VisualStudios/Application/Application/Core/Networking/Headers/NetworkConnection.h"
    "D:/Coding/VisualStudios/Application/Application/Core/Networking/Headers/NetworkData.h"
    "D:/Coding/VisualStudios/Application/Application/Core/Networking/Headers/NetworkMap.h"
    "D:/Coding/VisualStudios/Application/Application/Core/Networking/Headers/NetworkProtocol.h"
    "D:/Coding/VisualStudios/Application/Application/Core/Networking/Headers/NetworkReceiver.h"
    "D:/Coding/VisualStudios/Application/Application/Core/Networking/Headers/NetworkSender.h"
    "D:/Coding/VisualStudios/Application/Application/Core/Networking/Headers/Utils.h"
    "D:/Coding/VisualStudios/Application/Application/Core/Serialization/Headers/Serialization.h"
    "D:/Coding/VisualStudios/Application/Application/Core/Serialization/Headers/SerializationDefs.h"
    "D:/Coding/VisualStudios/Application/Application/Core/Serialization/Headers/SerializationUtils.h"
    "D:/Coding/VisualStudios/Application/Application/Core/UnitTests/HashTesting.h"
    )
endif()

