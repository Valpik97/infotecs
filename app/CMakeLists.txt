add_executable(logger_app main.cpp)

option(USE_SHARED "Use shared logger library" OFF)

if(USE_SHARED)
    target_link_libraries(logger_app PRIVATE logger_shared)
else()
    target_link_libraries(logger_app PRIVATE logger_static)
endif()

target_include_directories(logger_app PRIVATE ${CMAKE_SOURCE_DIR}/logger/include)
