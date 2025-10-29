project(Geometry)

set(SOURCES vec2.cpp figures/pentagon.cpp figures/rhombus.cpp figures/trapezoid.cpp)

add_library(geometry ${SOURCES})

target_include_directories(geometry PUBLIC ${CMAKE_CURRENT_SOURCE_DIR} ${CMAKE_CURRENT_SOURCE_DIR}/figures)
