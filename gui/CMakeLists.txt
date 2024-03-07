# ==========================================================================
# UNLIMITED RIGHTS
# Contract No. W900KK-23-D-0001/W900KK-23-F-00023
# [Flight School Training Support Services (FSTSS)]
#
# Contractor Name: Applied Visual Technology, Inc.
#                  (d/b/a AVT Simulation)
#
# Contractor Address: 4715 Data Court
#                     Orlando, Florida 32817
#
# SECURITY CLASSIFICATION: Unclassified
#
# WARNING: This software contains data whose export is restricted by the Arms
# Export Control Act (Title 22, U.S.C., Section 2751 et seq.) or the Export
# Administration Act of 1979, as amended, Title 50, U.S.C, APP. 2401 et seq.
#
# Copyright © 2023, 2024
# Applied Visual Technology, Inc. (d/b/a AVT Simulation)
# Unpublished Work - All Rights Reserved
# ==========================================================================
cmake_minimum_required(VERSION 3.2)

project(sptr)

find_package(glfw3 REQUIRED)

set(SOURCES
    app.cpp
    glfw_opengl_imgui_layer.cpp
)

find_package(OpenGL REQUIRED)

add_library(imgui_app STATIC ${SOURCES})
target_compile_definitions(imgui_app PRIVATE -DIMGUI_IMPL_OPENGL_LOADER_GLFW -DIMGUI_FREETYPE_ENABLE)
target_link_libraries(imgui_app PUBLIC imgui glfw OpenGL::GL util)
target_include_directories(imgui_app PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})


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

add_subdirectory(imgui-docking)

add_executable(sptr sptr.cpp )
target_link_options(sptr PRIVATE ${SUBSYSTEM_LINKER_OPTIONS})
target_link_libraries(sptr PRIVATE imgui_app notcute sptr_core game_engine)

# configure_file(compact.ini ${CMAKE_CURRENT_BINARY_DIR}/imgui.ini COPYONLY)

# file(COPY ${RESOURCES_DIR}/fonts DESTINATION ${CMAKE_CURRENT_BINARY_DIR}/resources)

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
