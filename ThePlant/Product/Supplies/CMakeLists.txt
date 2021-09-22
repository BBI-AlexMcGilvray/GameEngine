# dependencies on Materials

message("Configuring Supplies")

set(SOURCE_FILES #
)

set(HEADER_FILES #
Assets.h #
CustomAssets.h)

install(FILES ${HEADER_FILES} DESTINATION Supplies_Lib)

add_library(Supplies_Lib INTERFACE)
target_link_libraries(Supplies_Lib INTERFACE Materials_Lib)
target_include_directories(Supplies_Lib
    INTERFACE
        ${CMAKE_CURRENT_SOURCE_DIR}/..
)