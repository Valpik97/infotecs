add_library(logger_static STATIC
    src/LoggerFile.cpp
)

add_library(logger_shared SHARED
    src/LoggerFile.cpp
)

target_include_directories(logger_static PUBLIC
    ${CMAKE_CURRENT_SOURCE_DIR}/include
)

target_include_directories(logger_shared PUBLIC
    ${CMAKE_CURRENT_SOURCE_DIR}/include
)
