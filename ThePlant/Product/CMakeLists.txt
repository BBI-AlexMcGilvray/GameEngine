# dependencies on Pipeline, Materials, and Supplies libraries

message("Configuring Product")

set(SOURCE_FILES #
Source/CameraController.cpp #
Source/MyProduct.cpp #
Source/ProductManager.cpp)

set(HEADER_FILES #
Source/CameraController.h #
Headers/MyProduct.h #
Headers/ProductManager.h)

install(FILES ${HEADER_FILES} DESTINATION Product_Lib)

add_subdirectory(Supplies)

add_library(Product_Lib STATIC ${SOURCE_FILES})
target_link_libraries(Product_Lib Pipeline_Lib Materials_Lib Supplies_Lib)

target_include_directories(Product_Lib
    PUBLIC
        ${CMAKE_CURRENT_SOURCE_DIR}/..
)