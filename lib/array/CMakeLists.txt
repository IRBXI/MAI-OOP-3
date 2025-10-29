project(Array)

set(SOURCES array.cpp)
add_library(array ${SOURCES})

target_link_libraries(array PRIVATE geometry)
target_include_directories(array PUBLIC ${CMAKE_CURRENT_SOURCE_DIR} ${CMAKE_CURRENT_SOURCE_DIR}/../geometry/)
