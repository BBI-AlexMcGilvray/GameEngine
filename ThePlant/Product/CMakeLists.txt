# dependencies on Pipeline, Materials, and Supplies libraries

message("Configuring Product")

add_subdirectory(Dependencies)

set(SOURCE_FILES #
Scripting/LuaManager.cpp #
Source/CameraController.cpp #
Source/WorldInteractor.cpp #
Source/MyProduct.cpp #
Source/MyState.cpp #
Source/ProductManager.cpp #
Source/RegisterUtils.cpp #
Testing/TestingUtils.cpp #
Testing/TestSystem.cpp)

set(HEADER_FILES #
Scripting/LuaManager.h #
Headers/CameraController.h #
Headers/WorldInteractor.h #
Headers/MyProduct.h #
Headers/MyState.h #
Headers/ProductManager.h #
Headers/RegisterUtils.h #
Testing/TestingUtils.h #
Testing/TestSystem.h)

install(FILES ${HEADER_FILES} DESTINATION Product_Lib)

add_subdirectory(Supplies)

add_library(Product_Lib STATIC ${SOURCE_FILES})
target_link_libraries(Product_Lib Pipeline_Lib Materials_Lib Supplies_Lib Product_Dependencies_Lib)

target_include_directories(Product_Lib
    PUBLIC
        ${CMAKE_CURRENT_SOURCE_DIR}/..
)