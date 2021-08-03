# dependencies on Data library

message("Configuring Resources")

# set(SOURCE_FILES )

set(HEADER_FILES #
Assets.h #
CustomAssets.h #
MaterialAssets.h #
MeshAssets.h)

install(FILES ${HEADER_FILES} DESTINATION Resources)

add_library(Resources INTERFACE)
target_link_libraries(Resources INTERFACE Data Core)