cmake_minimum_required(VERSION 3.8)

set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

list(APPEND CMAKE_MODULE_PATH "${CMAKE_CURRENT_SOURCE_DIR}/./cmake")

find_package(SFML COMPONENTS graphics window system)
include_directories(${SFML_INCLUDE_DIR})

add_executable(tetris main.cpp)
target_link_libraries(tetris ${SFML_LIBRARIES})
