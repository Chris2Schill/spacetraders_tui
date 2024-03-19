
cmake_minimum_required(VERSION 3.2)

project(sptr_core)
#
# set(CMAKE_CXX_STANDARD 20)
# set(CMAKE_CXX_STANDARD_REQUIRED ON)
# set(CMAKE_CXX_EXTENSIONS OFF)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)


set(SOURCES
    src/api.cpp
)

find_package(spdlog REQUIRED)

add_library(sptr_core STATIC ${SOURCES})
target_include_directories(sptr_core PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/include)
target_link_libraries(sptr_core PUBLIC CppRestOpenAPIClient spdlog::spdlog)

# configure_file("users.ini" "${CMAKE_BINARY_DIR}")
