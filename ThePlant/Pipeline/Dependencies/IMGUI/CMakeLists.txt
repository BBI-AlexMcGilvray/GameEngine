message("Configuring IMGUI")

set(SOURCE_FILES #
imgui_draw.cpp #
imgui_tables.cpp #
imgui_widgets.cpp #
imgui.cpp #
backends/imgui_impl_opengl3.cpp #
backends/imgui_impl_sdl.cpp)

set(HEADER_FILES #
imconfig.h #
imgui_internal.h #
imgui.h #
imstb_rectpack.h #
imstb_textecit.h #
imstb_truetype.h #
backends/imgui_impl_opengl3.h #
backends/imgui_impl_sdl.h)

add_library(IMGUI_Lib STATIC ${SOURCE_FILES})
install(FILES ${HEADER_FILES} DESTINATION IMGUI_Lib)
target_link_libraries(IMGUI_Lib Materials_Lib)
target_include_directories(IMGUI_Lib
    PUBLIC
        ${CMAKE_CURRENT_SOURCE_DIR}/..
)