# dependencies on Materials

message("Configuring Supplies")

set(SOURCE_FILES #
)

set(HEADER_FILES #
Assets.h #
CustomAssets.h)

install(FILES ${HEADER_FILES} DESTINATION SuppliesLib)

add_library(SuppliesLib INTERFACE)
target_link_libraries(Product_Lib Materials_Lib)
target_include_directories(Product_Lib
    INTERFACE
        ${CMAKE_CURRENT_SOURCE_DIR}/..
)