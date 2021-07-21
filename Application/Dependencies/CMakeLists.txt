# include the libraries
include(ExternalProject)

message("Configurating Dependencies")

# ExternalProject_Add(GLEW
#     PREFIX ${CMAKE_CURRENT_SOURCE_DIR}/glew-2.1.0
#   SOURCE_DIR ${CMAKE_CURRENT_SOURCE_DIR}/glew-2.1.0/build
#    BINARY_DIR ${CMAKE_CURRENT_SOURCE_DIR}/glew-2.1.0/build
#    BUILD_COMMAND cmake --build . --config RELEASE
#    INSTALL_COMMAND 
#    BUILD_BYPRODUCTS <INSTALL_DIR>/build/lib/Release/libglew32.lib
#)
# ExternalProject_Get_Property(GLEW INSTALL_DIR)
# set(GLEW_INSTALL_DIR ${INSTALL_DIR})
# find_library(GLEW_LIB NAMES libglew32
#    PATHS ${INSTALL_DIR}/build/lib/Release)
# if(NOT GLEW_LIB)
#     message("Could not find GLEW_LIB")
# endif(NOT GLEW_LIB)

find_package(GLEW REQUIRED)

add_subdirectory(SDL2-2.0.14) # find out how to make sdl2 use release

add_library(Dependencies INTERFACE)
target_link_libraries(Dependencies
    INTERFACE
        SDL2main
        SDL2-static
        GLEW::glew_s
)
target_include_directories(Dependencies
    INTERFACE 
        glew-2.1.0/include
        SDL2-2.0.14/include    
)