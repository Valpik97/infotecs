cmake_minimum_required(VERSION 3.10)
project(LoggerProject)

set(CMAKE_CXX_STANDARD 17)

option(BUILD_SHARED_LIBS "Build shared libraries instead of static" OFF)

add_subdirectory(src)
add_subdirectory(app)
