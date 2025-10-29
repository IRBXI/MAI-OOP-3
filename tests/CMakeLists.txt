project(Tests)

include(FetchContent)
FetchContent_Declare(
  googletest
  GIT_REPOSITORY https://github.com/google/googletest.git
  GIT_TAG v1.15.0
  TLS_VERIFY false
)
FetchContent_MakeAvailable(googletest)

enable_testing()

add_subdirectory(figures)

add_executable(array_of_figures array_of_figures.cpp)
target_link_libraries(array_of_figures geometry array gtest_main)

add_executable(unit test_main.cpp figures/pentagon.cpp figures/rhombus.cpp figures/trapezoid.cpp array_of_figures.cpp)
target_link_libraries(unit geometry array gtest_main)
