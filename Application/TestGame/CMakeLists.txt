# dependencies on Application and Resources libraries

message("Configuring TestGame")

set(SOURCE_FILES #
# include source
)

set(HEADER_FILES #
# include headers
)

install(FILES ${HEADER_FILES} DESTINATION TestGame)

add_library(TestGame STATIC ${SOURCE_FILES})
target_link_libraries(TestGame ApplicationManagement Core Data Resources)