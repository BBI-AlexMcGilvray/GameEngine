# dependencies on Core library

message("Configuring Data")

set(SOURCE_FILES #
Rendering/Source/AnimatedMeshData.cpp #
Rendering/Source/AnimatedModelData.cpp #
Rendering/Source/MaterialData.cpp #
Rendering/Source/SimpleMeshData.cpp #
Rendering/Source/SimpleModelData.cpp #
Rendering/Source/SkeletonAnimationData.cpp #
Rendering/Source/SkeletonData.cpp #
Rendering/Source/StaticMeshData.cpp #
Rendering/Source/StaticModelData.cpp #
Rendering/Source/TextureData.cpp #
Source/AssetUtils.cpp)

set(HEADER_FILES #
Headers/AssetData.h #
Headers/AssetExceptions.h #
Headers/AssetName.h #
Headers/AssetType.h #
Headers/AssetUtils.h #
Rendering/Headers/AnimatedMeshData.h #
Rendering/Headers/AnimatedModelData.h #
Rendering/Headers/MaterialData.h #
Rendering/Headers/SimpleMeshData.h #
Rendering/Headers/SimpleModelData.h #
Rendering/Headers/SkeletonAnimationData.h #
Rendering/Headers/SkeletonData.h #
Rendering/Headers/StaticMeshData.h #
Rendering/Headers/StaticModelData.h #
Rendering/Headers/TextureData.h #
Rendering/Headers/VertexBaseData.h)

install(FILES ${HEADER_FILES} DESTINATION Data)

add_library(Data STATIC ${SOURCE_FILES})
target_link_libraries(Data Core)