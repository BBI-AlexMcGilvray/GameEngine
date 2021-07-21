message("Configurating Core")

set(SOURCE_FILES #
Functionality/Source/Scheduler.cpp #
Geometric/2D/Source/Box.cpp #
Geometric/2D/Source/Circle.cpp #
Geometric/2D/Source/GeometryFunctions.cpp #
Geometric/2D/Source/Line.cpp #
Geometric/2D/Source/Point.cpp #
Geometric/2D/Source/Polygon.cpp #
Geometric/Source/Transform.cpp #
IO/Source/File.cpp #
IO/Source/Folder.cpp #
IO/Source/IOUtils.cpp #
Math/Source/UtilityFunctions.cpp #
Math/UnitTests/MatrixTests.cpp #
Math/UnitTests/VectorTests.cpp #
Networking/Source/NetworkProtocol.cpp #
Networking/Source/Utils.cpp #
Source/Exception.cpp #
Source/Hash.cpp #
UnitTests/HashTesting.cpp #
CoreUnitTests.cpp)

set(HEADER_FILES #
Debugging/Headers/Declarations.h #
Debugging/Headers/Macros.h #
Functionality/Headers/Event.h #
Functionality/Headers/Function.h #
Functionality/Headers/LockerBase.h #
Functionality/Headers/Scheduler.h #
Functionality/Headers/Subscription.h #
Geometric/2D/Headers/Box.h #
Geometric/2D/Headers/Circle.h #
Geometric/2D/Headers/Geometry.h #
Geometric/2D/Headers/GeometryFunctions.h #
Geometric/2D/Headers/Line.h #
Geometric/2D/Headers/Point.h #
Geometric/2D/Headers/Polygon.h #
Geometric/Headers/GeometryDefs.h #
Geometric/Headers/Transform.h #
Headers/AllCore.h #
Headers/CoreDefs.h #
Headers/Exception.h #
Headers/FlagEnum.h #
Headers/Hash.h #
Headers/ListDefs.h #
Headers/MapDefs.h #
Headers/Property.h #
Headers/PtrDefs.h #
Headers/TemplateDefs.h #
Headers/TimeDefs.h #
IO/Headers/Exception.h #
IO/Headers/File.h #
IO/Headers/Folder.h #
IO/Headers/IODefs.h #
IO/Headers/IOUtils.h #
Math/Headers/Axis.h #
Math/Headers/Basis.h #
Math/Headers/Color.h #
Math/Headers/MathDefs.h #
Math/Headers/MathUtils.h #
Math/Headers/Matrix.h #
Math/Headers/Matrix2x2.h #
Math/Headers/Matrix3x3.h #
Math/Headers/Matrix4x4.h #
Math/Headers/MatrixFunctions.h #
Math/Headers/Quaternion.h #
Math/Headers/QuaternionFunctions.h #
Math/Headers/UtilityFunctions.h #
Math/Headers/Vector.h #
Math/Headers/Vector2.h #
Math/Headers/Vector3.h #
Math/Headers/Vector4.h #
Math/Headers/VectorFunctions.h #
Math/UnitTests/MathUnitTests.h #
Math/UnitTests/MatrixTests.h #
Math/UnitTests/VectorTests.h #
Networking/Headers/Macros.h #
Networking/Headers/NetworkConnection.h #
Networking/Headers/NetworkData.h #
Networking/Headers/NetworkMap.h #
Networking/Headers/NetworkProtocol.h #
Networking/Headers/NetworkReceiver.h #
Networking/Headers/NetworkSender.h #
Networking/Headers/Utils.h #
Serialization/Headers/Serialization.h #
Serialization/Headers/SerializationDefs.h #
Serialization/Headers/SerializationUtils.h #
UnitTests/HashTesting.h)

add_library(Core STATIC ${SOURCE_FILES})
install(FILES ${HEADER_FILES} DESTINATION Core)
target_include_directories(Core
    PUBLIC
        ${CMAKE_CURRENT_SOURCE_DIR}/..
)