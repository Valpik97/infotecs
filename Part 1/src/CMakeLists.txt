file(GLOB SOURCES *.cpp)
add_library(logger ${SOURCES})

target_include_directories(logger PUBLIC ${CMAKE_SOURCE_DIR}/include)
