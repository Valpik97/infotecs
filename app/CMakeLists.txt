add_executable(logger_app main.cpp)

# Link to the shared library
if(USE_SHARED)
    target_link_libraries(logger_app PRIVATE logger_shared)
else()
    target_link_libraries(logger_app PRIVATE logger_static)
endif()

# Copy DLL after build (only needed for shared on Windows)
if(WIN32)
    add_custom_command(TARGET logger_app POST_BUILD
        COMMAND ${CMAKE_COMMAND} -E copy_if_different
            $<TARGET_FILE:logger_shared>
            $<TARGET_FILE_DIR:logger_app>
    )
endif()