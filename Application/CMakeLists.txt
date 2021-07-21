option(DEFAULT_APPLICATION "Enable default application" ON)
option(TEST_GAME "Enable test game" OFF)

add_subdirectory(ApplicationManagement)
add_subdirectory(Core)
add_subdirectory(Data)
add_subdirectory(Dependencies)
add_subdirectory(Resources)

# default application
if (DEFAULT_APPLICATION)
  message("Using default application")
  add_executable(default_application main.cpp)
  target_link_libraries(default_application
    PUBLIC  ApplicationManagement
            Core
            Data
            Dependencies
            Resources
    PRIVATE application_options
            application_warnings)
endif()

# test game
if (TEST_GAME)
  mesage("Using test game")
  add_subdirectory(TestGame)
  # in the future, this would be the game executable
  add_executable(default_application main.cpp)
  target_link_libraries(default_application
    PRIVATE application_options
            application_warnings)
endif()