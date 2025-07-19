add_executable(log_app main.cpp)
target_link_libraries(log_app logger)
target_include_directories(log_app PRIVATE ${CMAKE_SOURCE_DIR}/include)
