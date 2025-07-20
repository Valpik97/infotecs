cmake_minimum_required(VERSION 3.10)
project(LoggerProject)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Подключаем подпроекты
add_subdirectory(logger)
add_subdirectory(app)
