# dependencies on Core, Data, and Dependencies

message("Configuring Materials")

add_subdirectory(Core)
add_subdirectory(Data)
add_subdirectory(Dependencies)

add_library(Materials_Lib INTERFACE)
target_link_libraries(Materials_Lib 
    INTERFACE   Core_Lib
                Data_Lib
                Dependencies_Lib)
target_include_directories(Materials_Lib
    INTERFACE
        ${CMAKE_CURRENT_SOURCE_DIR}
)