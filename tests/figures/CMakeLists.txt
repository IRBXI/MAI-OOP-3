project(FiguresTests)

add_executable(pentagon ../test_main.cpp pentagon.cpp)
target_link_libraries(pentagon geometry gtest_main)

add_executable(rhombus ../test_main.cpp rhombus.cpp)
target_link_libraries(rhombus geometry gtest_main)

add_executable(trapezoid ../test_main.cpp trapezoid.cpp)
target_link_libraries(trapezoid geometry gtest_main)
