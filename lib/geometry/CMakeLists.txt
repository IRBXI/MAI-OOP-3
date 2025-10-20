project(Geometry)

set(SOURCES vec2.cpp figures/pentagon.cpp figures/rhombus.cpp figures/trapezoid.cpp)
set(HEADERS vec2.hpp figure.hpp figures/pentagon.hpp figures/rhombus.hpp figures/trapezoid.hpp)

add_library(geometry ${SOURCES} ${HEADERS})

target_include_directories(geometry PUBLIC ${CMAKE_CURRENT_SOURCE_DIR} ${CMAKE_CURRENT_SOURCE_DIR}/figures)
