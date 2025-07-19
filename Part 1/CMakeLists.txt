cmake_minimum_required(VERSION 3.10)
project(LoggerProject)

set(CMAKE_CXX_STANDARD 17)

# Библиотека
add_subdirectory(src)

# Приложение
add_subdirectory(app)
