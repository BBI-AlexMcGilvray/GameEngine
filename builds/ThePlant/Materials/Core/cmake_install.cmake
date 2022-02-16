# Install script for directory: D:/Coding/VisualStudios/Application/ThePlant/Materials/Core

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
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/Core_Lib" TYPE FILE FILES
    "D:/Coding/VisualStudios/Application/ThePlant/Materials/Core/Containers/CircularBuffer.h"
    "D:/Coding/VisualStudios/Application/ThePlant/Materials/Core/Debugging/Headers/Declarations.h"
    "D:/Coding/VisualStudios/Application/ThePlant/Materials/Core/Debugging/Headers/Macros.h"
    "D:/Coding/VisualStudios/Application/ThePlant/Materials/Core/Functionality/Headers/Event.h"
    "D:/Coding/VisualStudios/Application/ThePlant/Materials/Core/Functionality/Headers/Function.h"
    "D:/Coding/VisualStudios/Application/ThePlant/Materials/Core/Functionality/Headers/LockerBase.h"
    "D:/Coding/VisualStudios/Application/ThePlant/Materials/Core/Functionality/Headers/Scheduler.h"
    "D:/Coding/VisualStudios/Application/ThePlant/Materials/Core/Functionality/Headers/Subscription.h"
    "D:/Coding/VisualStudios/Application/ThePlant/Materials/Core/Geometric/2DFunctions.h"
    "D:/Coding/VisualStudios/Application/ThePlant/Materials/Core/Geometric/3DFunctions.h"
    "D:/Coding/VisualStudios/Application/ThePlant/Materials/Core/Geometric/Box.h"
    "D:/Coding/VisualStudios/Application/ThePlant/Materials/Core/Geometric/BoxFunctions.h"
    "D:/Coding/VisualStudios/Application/ThePlant/Materials/Core/Geometric/Circle.h"
    "D:/Coding/VisualStudios/Application/ThePlant/Materials/Core/Geometric/CircleFunctions.h"
    "D:/Coding/VisualStudios/Application/ThePlant/Materials/Core/Geometric/Functions.h"
    "D:/Coding/VisualStudios/Application/ThePlant/Materials/Core/Geometric/GeometryDefs.h"
    "D:/Coding/VisualStudios/Application/ThePlant/Materials/Core/Geometric/Line2D.h"
    "D:/Coding/VisualStudios/Application/ThePlant/Materials/Core/Geometric/Line2DFunctions.h"
    "D:/Coding/VisualStudios/Application/ThePlant/Materials/Core/Geometric/Line3D.h"
    "D:/Coding/VisualStudios/Application/ThePlant/Materials/Core/Geometric/Line3DFunctions.h"
    "D:/Coding/VisualStudios/Application/ThePlant/Materials/Core/Geometric/Plane.h"
    "D:/Coding/VisualStudios/Application/ThePlant/Materials/Core/Geometric/PlaneFunctions.h"
    "D:/Coding/VisualStudios/Application/ThePlant/Materials/Core/Geometric/Rectangle.h"
    "D:/Coding/VisualStudios/Application/ThePlant/Materials/Core/Geometric/RectangleFunctions.h"
    "D:/Coding/VisualStudios/Application/ThePlant/Materials/Core/Geometric/SphereFunctions.h"
    "D:/Coding/VisualStudios/Application/ThePlant/Materials/Core/Geometric/Sphere.h"
    "D:/Coding/VisualStudios/Application/ThePlant/Materials/Core/Geometric/Transform.h"
    "D:/Coding/VisualStudios/Application/ThePlant/Materials/Core/Headers/AllCore.h"
    "D:/Coding/VisualStudios/Application/ThePlant/Materials/Core/Headers/CoreDefs.h"
    "D:/Coding/VisualStudios/Application/ThePlant/Materials/Core/Headers/Exception.h"
    "D:/Coding/VisualStudios/Application/ThePlant/Materials/Core/Headers/FlagEnum.h"
    "D:/Coding/VisualStudios/Application/ThePlant/Materials/Core/Headers/Hash.h"
    "D:/Coding/VisualStudios/Application/ThePlant/Materials/Core/Headers/Macros.h"
    "D:/Coding/VisualStudios/Application/ThePlant/Materials/Core/Headers/PtrDefs.h"
    "D:/Coding/VisualStudios/Application/ThePlant/Materials/Core/Headers/Service.h"
    "D:/Coding/VisualStudios/Application/ThePlant/Materials/Core/Headers/TemplateDefs.h"
    "D:/Coding/VisualStudios/Application/ThePlant/Materials/Core/Headers/TimeDefs.h"
    "D:/Coding/VisualStudios/Application/ThePlant/Materials/Core/Headers/UtilityMacros.h"
    "D:/Coding/VisualStudios/Application/ThePlant/Materials/Core/IO/Headers/Exception.h"
    "D:/Coding/VisualStudios/Application/ThePlant/Materials/Core/IO/Headers/File.h"
    "D:/Coding/VisualStudios/Application/ThePlant/Materials/Core/IO/Headers/Folder.h"
    "D:/Coding/VisualStudios/Application/ThePlant/Materials/Core/IO/Headers/IODefs.h"
    "D:/Coding/VisualStudios/Application/ThePlant/Materials/Core/IO/Headers/IOUtils.h"
    "D:/Coding/VisualStudios/Application/ThePlant/Materials/Core/Logging/ConsoleLogger.h"
    "D:/Coding/VisualStudios/Application/ThePlant/Materials/Core/Logging/ILogger.h"
    "D:/Coding/VisualStudios/Application/ThePlant/Materials/Core/Logging/Logger.h"
    "D:/Coding/VisualStudios/Application/ThePlant/Materials/Core/Math/Headers/Axis.h"
    "D:/Coding/VisualStudios/Application/ThePlant/Materials/Core/Math/Headers/Basis.h"
    "D:/Coding/VisualStudios/Application/ThePlant/Materials/Core/Math/Headers/Color.h"
    "D:/Coding/VisualStudios/Application/ThePlant/Materials/Core/Math/Headers/MathDefs.h"
    "D:/Coding/VisualStudios/Application/ThePlant/Materials/Core/Math/Headers/MathUtils.h"
    "D:/Coding/VisualStudios/Application/ThePlant/Materials/Core/Math/Headers/Matrix.h"
    "D:/Coding/VisualStudios/Application/ThePlant/Materials/Core/Math/Headers/Matrix2x2.h"
    "D:/Coding/VisualStudios/Application/ThePlant/Materials/Core/Math/Headers/Matrix3x3.h"
    "D:/Coding/VisualStudios/Application/ThePlant/Materials/Core/Math/Headers/Matrix4x4.h"
    "D:/Coding/VisualStudios/Application/ThePlant/Materials/Core/Math/Headers/MatrixFunctions.h"
    "D:/Coding/VisualStudios/Application/ThePlant/Materials/Core/Math/Headers/Quaternion.h"
    "D:/Coding/VisualStudios/Application/ThePlant/Materials/Core/Math/Headers/QuaternionFunctions.h"
    "D:/Coding/VisualStudios/Application/ThePlant/Materials/Core/Math/Headers/UtilityFunctions.h"
    "D:/Coding/VisualStudios/Application/ThePlant/Materials/Core/Math/Headers/Vector.h"
    "D:/Coding/VisualStudios/Application/ThePlant/Materials/Core/Math/Headers/Vector2.h"
    "D:/Coding/VisualStudios/Application/ThePlant/Materials/Core/Math/Headers/Vector3.h"
    "D:/Coding/VisualStudios/Application/ThePlant/Materials/Core/Math/Headers/Vector4.h"
    "D:/Coding/VisualStudios/Application/ThePlant/Materials/Core/Math/Headers/VectorFunctions.h"
    "D:/Coding/VisualStudios/Application/ThePlant/Materials/Core/Math/UnitTests/MathUnitTests.h"
    "D:/Coding/VisualStudios/Application/ThePlant/Materials/Core/Math/UnitTests/MatrixTests.h"
    "D:/Coding/VisualStudios/Application/ThePlant/Materials/Core/Math/UnitTests/VectorTests.h"
    "D:/Coding/VisualStudios/Application/ThePlant/Materials/Core/Networking/Headers/Macros.h"
    "D:/Coding/VisualStudios/Application/ThePlant/Materials/Core/Networking/Headers/NetworkConnection.h"
    "D:/Coding/VisualStudios/Application/ThePlant/Materials/Core/Networking/Headers/NetworkData.h"
    "D:/Coding/VisualStudios/Application/ThePlant/Materials/Core/Networking/Headers/NetworkMap.h"
    "D:/Coding/VisualStudios/Application/ThePlant/Materials/Core/Networking/Headers/NetworkProtocol.h"
    "D:/Coding/VisualStudios/Application/ThePlant/Materials/Core/Networking/Headers/NetworkReceiver.h"
    "D:/Coding/VisualStudios/Application/ThePlant/Materials/Core/Networking/Headers/NetworkSender.h"
    "D:/Coding/VisualStudios/Application/ThePlant/Materials/Core/Networking/Headers/Utils.h"
    "D:/Coding/VisualStudios/Application/ThePlant/Materials/Core/Random/Functions.h"
    "D:/Coding/VisualStudios/Application/ThePlant/Materials/Core/Random/Random.h"
    "D:/Coding/VisualStudios/Application/ThePlant/Materials/Core/Random/RandomGenerator.h"
    "D:/Coding/VisualStudios/Application/ThePlant/Materials/Core/Reflection/Enums.h"
    "D:/Coding/VisualStudios/Application/ThePlant/Materials/Core/Reflection/Reflectable.h"
    "D:/Coding/VisualStudios/Application/ThePlant/Materials/Core/Reflection/ReflectableClasses.h"
    "D:/Coding/VisualStudios/Application/ThePlant/Materials/Core/Reflection/type_traits.h"
    "D:/Coding/VisualStudios/Application/ThePlant/Materials/Core/Serialization/Formats/Binary/Binary.h"
    "D:/Coding/VisualStudios/Application/ThePlant/Materials/Core/Serialization/Formats/JSON/JSON.h"
    "D:/Coding/VisualStudios/Application/ThePlant/Materials/Core/Serialization/Serialization.h"
    "D:/Coding/VisualStudios/Application/ThePlant/Materials/Core/Serialization/type_traits.h"
    "D:/Coding/VisualStudios/Application/ThePlant/Materials/Core/IdTypes/IncrementalId.h"
    "D:/Coding/VisualStudios/Application/ThePlant/Materials/Core/IdTypes/InstanceId.h"
    "D:/Coding/VisualStudios/Application/ThePlant/Materials/Core/IdTypes/RuntimeId.h"
    "D:/Coding/VisualStudios/Application/ThePlant/Materials/Core/IdTypes/UUID.h"
    "D:/Coding/VisualStudios/Application/ThePlant/Materials/Core/TypeSafety/NotNullPtr.h"
    "D:/Coding/VisualStudios/Application/ThePlant/Materials/Core/TypeSafety/SafeVoidPtr.h"
    "D:/Coding/VisualStudios/Application/ThePlant/Materials/Core/Versioning/SemanticVerion.h"
    "D:/Coding/VisualStudios/Application/ThePlant/Materials/Core/Versioning/SimpleVersion.h"
    "D:/Coding/VisualStudios/Application/ThePlant/Materials/Core/Versioning/Version.h"
    )
endif()

