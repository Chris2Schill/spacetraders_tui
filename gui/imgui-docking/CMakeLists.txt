cmake_minimum_required(VERSION 3.20)

project(imgui)

set(SOURCES
    imgui.cpp
    imgui_draw.cpp
    imgui_tables.cpp
    imgui_widgets.cpp
    imgui_demo.cpp
    misc/freetype/imgui_freetype.cpp
    backends/imgui_impl_glfw.cpp
    backends/imgui_impl_opengl3.cpp
)

add_library(imgui STATIC ${SOURCES})
target_include_directories(imgui PUBLIC
    ${CMAKE_CURRENT_SOURCE_DIR}
    ${CMAKE_CURRENT_SOURCE_DIR}/backends
    $ENV{MINGW64_ROOT}/include/freetype2
    /usr/include/freetype2
)

file(GLOB HEADERS *.h backends/*.h)
target_link_libraries(imgui PUBLIC freetype glfw)

install(FILES ${HEADERS}
        DESTINATION include
)

install(TARGETS imgui
        DESTINATION lib
)
