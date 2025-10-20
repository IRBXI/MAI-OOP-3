project(Array)

set(SOURCES array.cpp)
set(HEADERS array.hpp)
add_library(array ${SOURCES} ${HEADERS})

target_link_libraries(array PRIVATE geometry)
target_include_directories(array PUBLIC ${CMAKE_CURRENT_SOURCE_DIR} ${CMAKE_CURRENT_SOURCE_DIR}/../geometry/)
