message("Configuring Dependencies")

add_subdirectory(IMGUI) # find out how to make INGUI use release/debug properly

add_library(Pipeline_Dependencies_Lib INTERFACE)
target_link_libraries(Pipeline_Dependencies_Lib
    INTERFACE
        IMGUI_Lib
)
# the dependency includes should not be referenced directly
# instead they should be wrapped in a file in the Include directory
# this allows us to control how they are affected by clang-format 
target_include_directories(Pipeline_Dependencies_Lib
    INTERFACE 
        IMGUI
)