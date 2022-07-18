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
Source/AssetLocationMapping.cpp #
Source/AssetManager.cpp #
Source/SerializationUtils.cpp)

set(HEADER_FILES #
Headers/AssetData.h #
Headers/AssetExceptions.h #
Headers/AssetLocation.h #
Headers/AssetLocationMapping.h #
Headers/AssetMacros.h #
Headers/AssetManager.h #
Headers/AssetName.h #
Headers/AssetType.h #
Headers/SerializationUtils.h #
Rendering/Headers/AnimatedMeshData.h #
Rendering/Headers/AnimatedModelData.h #
Rendering/Headers/MaterialData.h #
Rendering/Headers/SimpleMeshData.h #
Rendering/Headers/SimpleModelData.h #
Rendering/Headers/SkeletonAnimationData.h #
Rendering/Headers/SkeletonData.h #
Rendering/Headers/StaticMeshData.h #
Rendering/Headers/StaticModelData.h #
Rendering/Headers/TextureData.h)

install(FILES ${HEADER_FILES} DESTINATION Data_Lib)

add_library(Data_Lib STATIC ${SOURCE_FILES})
target_link_libraries(Data_Lib Core_Lib)