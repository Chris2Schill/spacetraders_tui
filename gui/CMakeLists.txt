cmake_minimum_required(VERSION 3.2)

project(gui)


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
)

add_executable(sptr ${SOURCES})
target_link_options(sptr PRIVATE ${SUBSYSTEM_LINKER_OPTIONS})
target_link_libraries(sptr PRIVATE game_engine)

file(COPY scripts DESTINATION ${CMAKE_CURRENT_BINARY_DIR})
file(COPY ../spacetraders-sdk/liblua/openapiclient DESTINATION ${CMAKE_CURRENT_BINARY_DIR})

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
