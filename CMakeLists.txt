
cmake_minimum_required(VERSION 3.2)


set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

project(spacetraders VERSION 0.1)

if(WIN32 AND NOT MSVC)
    add_compile_options(-Wall -fuse-ld=lld)
elseif(UNIX)
    add_compile_options(-Wall)
endif()

#TODO fix this properly by adding an install to BSI libraries

add_subdirectory(spacetraders-sdk)
add_subdirectory(notcute)

set(SOURCES
    main.cpp
    sptr_api.cpp
)

find_package(spdlog REQUIRED)

add_executable(spacetraders ${SOURCES})
target_link_libraries(spacetraders PRIVATE notcute CppRestOpenAPIClient spdlog::spdlog)
target_link_directories(spacetraders PRIVATE /usr/local/lib)

configure_file("users.ini" "${CMAKE_BINARY_DIR}")
