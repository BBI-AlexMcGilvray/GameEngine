option(PIPELINE "Enable test game" ON) # the engine
option(FACTORY "Enable default application" ON) # the editor
option(PRODUCT "Enable product" ON) # the game

# this is needed if we want to link to GLEW statically
add_compile_definitions(GLEW_STATIC)

# all options rely on Materials and Pipeline
add_subdirectory(Materials)
add_subdirectory(Pipeline)

# engine
if (PIPELINE)
  message("Generating Pipeline")

  add_executable(Pipeline Pipeline/Pipeline.cpp)
  target_link_libraries(Pipeline
    PUBLIC  Pipeline_Lib
            Materials_Lib
    PRIVATE build_options
            build_warnings)
 
  # ideally this is cleaner, may not scale based on config and such
  add_custom_command(TARGET Pipeline POST_BUILD
        COMMAND ${CMAKE_COMMAND} -E copy
                "${CMAKE_CURRENT_BINARY_DIR}/$<CONFIG>/Pipeline.exe"
                "${CMAKE_CURRENT_BINARY_DIR}/$<CONFIG>/Pipeline/Pipeline.exe"
        COMMAND ${CMAKE_COMMAND} -E copy
                "${CMAKE_CURRENT_BINARY_DIR}/$<CONFIG>/Pipeline.pdb"
                "${CMAKE_CURRENT_BINARY_DIR}/$<CONFIG>/Pipeline/Pipeline.pdb"
        COMMAND ${CMAKE_COMMAND} -E copy_directory
                "${CMAKE_CURRENT_SOURCE_DIR}/Resources/Exported"
                "${CMAKE_CURRENT_BINARY_DIR}/$<CONFIG>/Pipeline/Resources")
endif()

# editor
if (FACTORY)
# not sure why this seems to be generating additional files (*.lib and *.exp)
  message("Generating Factory")

  # only Factory relies on Factory
  add_subdirectory(Factory)

  add_executable(Factory Factory/Factory.cpp)
  target_link_libraries(Factory
    PUBLIC  Factory_Lib
            Pipeline_Lib
            Materials_Lib
    PRIVATE build_options
            build_warnings)

  add_custom_command(TARGET Factory POST_BUILD
        COMMAND ${CMAKE_COMMAND} -E copy
                "${CMAKE_CURRENT_BINARY_DIR}/$<CONFIG>/Factory.exe"
                "${CMAKE_CURRENT_BINARY_DIR}/$<CONFIG>/Factory/Factory.exe"
        COMMAND ${CMAKE_COMMAND} -E copy
                "${CMAKE_CURRENT_BINARY_DIR}/$<CONFIG>/Factory.pdb"
                "${CMAKE_CURRENT_BINARY_DIR}/$<CONFIG>/Factory/Factory.pdb"
        COMMAND ${CMAKE_COMMAND} -E copy_directory
                "${CMAKE_CURRENT_SOURCE_DIR}/Resources/Imported"
                "${CMAKE_CURRENT_BINARY_DIR}/$<CONFIG>/Factory/Resources")
endif()

# game
if (PRODUCT)
  message("Generating Product")

  # only Product relies on Product
  add_subdirectory(Product)

  add_executable(Product Product/Product.cpp)
  target_link_libraries(Product
    PUBLIC  Product_Lib
            Pipeline_Lib
            Materials_Lib
    PRIVATE build_options
            build_warnings)

  add_custom_command(TARGET Product POST_BUILD
        COMMAND ${CMAKE_COMMAND} -E copy
                "${CMAKE_CURRENT_BINARY_DIR}/$<CONFIG>/Product.exe"
                "${CMAKE_CURRENT_BINARY_DIR}/$<CONFIG>/Product/Product.exe"
        COMMAND ${CMAKE_COMMAND} -E copy
                "${CMAKE_CURRENT_BINARY_DIR}/$<CONFIG>/Product.pdb"
                "${CMAKE_CURRENT_BINARY_DIR}/$<CONFIG>/Product/Product.pdb"
        COMMAND ${CMAKE_COMMAND} -E copy_directory
                "${CMAKE_CURRENT_SOURCE_DIR}/Resources/Exported"
                "${CMAKE_CURRENT_BINARY_DIR}/$<CONFIG>/Product/Resources")
endif()