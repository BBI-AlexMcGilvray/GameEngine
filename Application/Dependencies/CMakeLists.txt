# include the libraries
include(ExternalProject)

message("Configurating Dependencies")

add_subdirectory(GLEW-2.2.0) # find out how to make glew use release
add_subdirectory(SDL2-2.0.14) # find out how to make sdl2 use release

add_library(Dependencies INTERFACE)
target_link_libraries(Dependencies
    INTERFACE
        SDL2main
        SDL2-static
        libglew_static
)
target_include_directories(Dependencies
    INTERFACE 
        glew-2.2.0/include
        SDL2-2.0.14/include    
)