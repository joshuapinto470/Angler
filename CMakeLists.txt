cmake_minimum_required(VERSION 3.15)
set (CMAKE_CXX_STANDARD 17)

project(Angler)

add_subdirectory(AnglerRT)
add_subdirectory(AnglerED)
add_subdirectory(tools/tinyobjloader)
add_subdirectory(libs/spdlog)
