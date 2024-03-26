cmake_minimum_required(VERSION 3.2)

project(gui)

find_package(OpenGL REQUIRED)
find_package(glfw3 REQUIRED)

add_subdirectory(vendor/imgui-docking)
add_subdirectory(vendor/SFML)

set(IMGUI_DIR vendor/imgui-docking)
add_subdirectory(vendor/imgui-sfml)


set(SOURCES
    app.cpp
    glfw_opengl_imgui_layer.cpp
)



add_library(imgui_app STATIC ${SOURCES})
target_compile_definitions(imgui_app PRIVATE -DIMGUI_IMPL_OPENGL_LOADER_GLFW -DIMGUI_FREETYPE_ENABLE sfml_graphics)
target_link_libraries(imgui_app PUBLIC imgui glfw OpenGL::GL util)
target_include_directories(imgui_app PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/vendor ${CMAKE_CURRENT_SOURCE_DIR})


if (WIN32)
    if (MSVC)
        set(SUBSYSTEM_LINKER_OPTIONS "/SUBSYSTEM:WINDOWS /ENTRY:mainCRTStartup")
    else()
        set(SUBSYSTEM_LINKER_OPTIONS "-mwindows")
    endif(MSVC)
else()
    # TODO test:
    # set(SUBSYSTEM_LINKER_OPTIONS "-m")
endif()


set(SOURCES
    sptr_sfml.cpp
    layers/map.cpp
)

add_executable(sptr ${SOURCES})
target_link_options(sptr PRIVATE ${SUBSYSTEM_LINKER_OPTIONS})
target_link_libraries(sptr PRIVATE imgui_app notcute sptr_core game_engine sfml-graphics ImGui-SFML::ImGui-SFML)

# configure_file(compact.ini ${CMAKE_CURRENT_BINARY_DIR}/imgui.ini COPYONLY)

# file(COPY ${RESOURCES_DIR}/fonts DESTINATION ${CMAKE_CURRENT_BINARY_DIR}/resources)
file(COPY scripts DESTINATION ${CMAKE_CURRENT_BINARY_DIR})
file(COPY ../spacetraders-sdk/liblua DESTINATION ${CMAKE_CURRENT_BINARY_DIR})

install(IMPORTED_RUNTIME_ARTIFACTS sptr
        RUNTIME_DEPENDENCY_SET sptr
)

install(RUNTIME_DEPENDENCY_SET sptr
        DESTINATION bin
        POST_EXCLUDE_REGEXES "api-ms-." "ext-ms-." "system32" "Windows"
        DIRECTORIES "$ENV{MINGW64_ROOT}/bin"
)

install(FILES compact.ini
        RENAME imgui.ini
        DESTINATION bin
)
install(FILES compact.ini
        DESTINATION bin/layouts
)
