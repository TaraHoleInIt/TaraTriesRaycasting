cmake_minimum_required(VERSION 3.10)

project(taara VERSION 1.0)

find_package(SDL2 REQUIRED)
include_directories(${SDL2_INCLUDE_DIRS})

set (CMAKE_CXX_STANDARD 11)

add_executable(taara main.cpp raycastercamera.cpp input.cpp world.cpp palette.cpp)
target_link_libraries(taara ${SDL2_LIBRARIES})


