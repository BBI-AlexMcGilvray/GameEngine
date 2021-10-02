message("Configuring Dependencies")

add_subdirectory(lua)
add_subdirectory(sol2-3.2.3) # find out how to make sol use release/debug properly

add_library(Product_Dependencies_Lib INTERFACE)
target_link_libraries(Product_Dependencies_Lib
    INTERFACE
        sol2
)
# the dependency includes should not be referenced directly
# instead they should be wrapped in a file in the Include directory
# this allows us to control how they are affected by clang-format 
target_include_directories(Product_Dependencies_Lib
    INTERFACE 
        sol2-3.2.3/include
)