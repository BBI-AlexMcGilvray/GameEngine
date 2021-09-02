# dependencies on Pipeline, Materials, and Resources libraries

message("Configuring Factory")

add_subdirectory(Workers)

set(SOURCE_FILES #
CustomData/Source/DataCreation.cpp #
CustomData/Source/DataExportDefs.cpp #
CustomData/Source/DataExportUtils.cpp #
Rendering/Source/AssimpExtensions.cpp #
Rendering/Source/MaterialExport.cpp #
Rendering/Source/MeshExport.cpp #
Rendering/Source/ModelExport.cpp #
Rendering/Source/SceneConversion.cpp #
Rendering/Source/SkeletonAnimationExport.cpp #
Rendering/Source/SkeletonExport.cpp #
Rendering/Source/TextureExport.cpp #
Rendering/Source/Utils.cpp #
Source/Config.cpp #
Source/ExportData.cpp #
SQL/Source/SQLInstance.cpp)

set(HEADER_FILES #
CustomData/Headers/DataCreation.h #
CustomData/Headers/DataExportDefs.h #
CustomData/Headers/DataExportUtils.h #
Headers/Config.h #
Headers/ExportData.h #
Headers/ExportException.h #
Rendering/Headers/AssimpExtensions.h #
Rendering/Headers/MaterialExport.h #
Rendering/Headers/MeshExport.h #
Rendering/Headers/ModelExport.h #
Rendering/Headers/SceneConversion.h #
Rendering/Headers/SkeletonAnimationExport.h #
Rendering/Headers/SkeletonExport.h #
Rendering/Headers/TextureExport.h #
Rendering/Headers/Utils.h #
SQL/Headers/SQLDefs.h #
SQL/Headers/SQLExceptions.h #
SQL/Headers/SQLInstance.h)

install(FILES ${HEADER_FILES} DESTINATION Factory_Lib)

add_library(Factory_Lib STATIC ${SOURCE_FILES})
target_link_libraries(Factory_Lib Pipeline_Lib Materials_Lib Workers_Lib)
target_include_directories(Factory_Lib
    PUBLIC
        ${CMAKE_CURRENT_SOURCE_DIR}/..
)