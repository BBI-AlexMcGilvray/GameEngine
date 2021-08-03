# include the libraries
include(ExternalProject)

message("Configuring Dependencies")

add_subdirectory(GLEW-2.2.0) # find out how to make glew use release
add_subdirectory(SDL2-2.0.14) # find out how to make sdl2 use release

add_library(Dependencies INTERFACE)
target_link_libraries(Dependencies
    INTERFACE
        SDL2main
        SDL2-static
        libglew_static
)
# the dependency includes should not be referenced directly
# instead they should be wrapped in a file in the Include directory
# this allows us to control how they are affected by clang-format 
target_include_directories(Dependencies
    INTERFACE
        Includes
        glew-2.2.0/include
        SDL2-2.0.14/include    
)