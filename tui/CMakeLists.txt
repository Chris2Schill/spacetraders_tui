
cmake_minimum_required(VERSION 3.2)

project(tui VERSION 0.1)

if(WIN32 AND NOT MSVC)
    add_compile_options(-Wall -fuse-ld=lld)
elseif(UNIX)
    add_compile_options(-Wall)
endif()

set(SOURCES
    main.cpp
)

find_package(spdlog REQUIRED)

add_subdirectory(vendor/notcute)

# add_executable(spacetraders ${SOURCES})
# target_link_libraries(spacetraders PRIVATE notcute CppRestOpenAPIClient spdlog::spdlog sptr_core)
# target_link_directories(spacetraders PRIVATE /usr/local/lib)

configure_file("../users.ini" "${CMAKE_BINARY_DIR}")
