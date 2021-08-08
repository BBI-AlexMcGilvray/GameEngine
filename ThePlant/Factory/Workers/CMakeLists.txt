# include the libraries
include(ExternalProject)

message("Configuring Workers")

add_subdirectory(assimp-5.0.1) # find out how to make assimp use release
add_subdirectory(SQLiteCpp-3.1.1) # find out how to make sqlite use release

add_library(Workers_Lib INTERFACE)
target_link_libraries(Workers_Lib
    INTERFACE
        assimp
        SQLiteCpp
        sqlite3
)
# the dependency includes should not be referenced directly
# instead they should be wrapped in a file in the Include directory
# this allows us to control how they are affected by clang-format 
target_include_directories(Workers_Lib
    INTERFACE
        Includes
        assimp-5.0.1/include
        SQLiteCpp-3.1.1/include 
        SQLiteCpp-3.1.1/sqlite3   
)