add_executable(logger_tests test_logger.cpp)

if(USE_SHARED)
    target_link_libraries(logger_tests PRIVATE logger_shared)
else()
    target_link_libraries(logger_tests PRIVATE logger_static)
endif()

target_include_directories(logger_tests PRIVATE
    ${CMAKE_SOURCE_DIR}/logger/include
) 