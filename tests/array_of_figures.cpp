#include "array.hpp"
#include "pentagon.hpp"
#include "rhombus.hpp"
#include "trapezoid.hpp"
#include <cmath>
#include <gtest/gtest.h>
#include <iostream>
#include <sstream>
#include <string>

class ArrayFigurePointerTest : public ::testing::Test {
  protected:
    void SetUp() override {
        // Create various figures for testing
        pentagon1 = new lib::geometry::Pentagon(lib::geometry::Vec2(0, 0),
                                                lib::geometry::Vec2(1, 0));
        pentagon2 = new lib::geometry::Pentagon(lib::geometry::Vec2(2, 2),
                                                lib::geometry::Vec2(2, 0));

        rhombus1 = new lib::geometry::Rhombus(lib::geometry::Vec2(0, 0),
                                              lib::geometry::Vec2(3, 0),
                                              M_PI / 3 // 60 degrees
        );
        rhombus2 = new lib::geometry::Rhombus(lib::geometry::Vec2(1, 1),
                                              lib::geometry::Vec2(2, 0),
                                              M_PI / 4 // 45 degrees
        );

        trapezoid1 = new lib::geometry::Trapezoid(lib::geometry::Vec2(0, 0),
                                                  lib::geometry::Vec2(4, 0),
                                                  M_PI / 4, // 45 degrees
                                                  2.0);
        trapezoid2 = new lib::geometry::Trapezoid(lib::geometry::Vec2(3, 3),
                                                  lib::geometry::Vec2(5, 0),
                                                  M_PI / 3, // 60 degrees
                                                  3.0);
    }

    void TearDown() override {
        // Clean up all allocated figures
        delete pentagon1;
        delete pentagon2;
        delete rhombus1;
        delete rhombus2;
        delete trapezoid1;
        delete trapezoid2;
    }

    lib::geometry::Pentagon* pentagon1;
    lib::geometry::Pentagon* pentagon2;
    lib::geometry::Rhombus* rhombus1;
    lib::geometry::Rhombus* rhombus2;
    lib::geometry::Trapezoid* trapezoid1;
    lib::geometry::Trapezoid* trapezoid2;
};

// Test PrintCentroids with empty array
TEST_F(ArrayFigurePointerTest, PrintCentroidsEmpty) {
    lib::array::ArrayFigurePointer array;

    // Redirect cout to stringstream to capture output
    std::stringstream buffer;
    std::streambuf* old = std::cout.rdbuf(buffer.rdbuf());

    array.PrintCentroids();

    std::cout.rdbuf(old); // Restore cout

    std::string output = buffer.str();
    EXPECT_TRUE(output.empty()); // No output for empty array
}

// Test PrintCentroids with mixed figures
TEST_F(ArrayFigurePointerTest, PrintCentroidsMixedFigures) {
    lib::array::ArrayFigurePointer array = {pentagon1, rhombus1, trapezoid1};

    // Redirect cout to stringstream to capture output
    std::stringstream buffer;
    std::streambuf* old = std::cout.rdbuf(buffer.rdbuf());

    array.PrintCentroids();

    std::cout.rdbuf(old); // Restore cout

    std::string output = buffer.str();

    // Should contain centroid information for all figures
    EXPECT_FALSE(output.empty());
    EXPECT_NE(output.find("Figure 0 centroid:"), std::string::npos);
    EXPECT_NE(output.find("Figure 1 centroid:"), std::string::npos);
    EXPECT_NE(output.find("Figure 2 centroid:"), std::string::npos);

    // All centroids should be finite
    lib::geometry::Vec2 centroid0 = pentagon1->Centroid();
    lib::geometry::Vec2 centroid1 = rhombus1->Centroid();
    lib::geometry::Vec2 centroid2 = trapezoid1->Centroid();

    EXPECT_TRUE(std::isfinite(centroid0.x));
    EXPECT_TRUE(std::isfinite(centroid0.y));
    EXPECT_TRUE(std::isfinite(centroid1.x));
    EXPECT_TRUE(std::isfinite(centroid1.y));
    EXPECT_TRUE(std::isfinite(centroid2.x));
    EXPECT_TRUE(std::isfinite(centroid2.y));
}

// Test PrintAreas with empty array
TEST_F(ArrayFigurePointerTest, PrintAreasEmpty) {
    lib::array::ArrayFigurePointer array;

    // Redirect cout to stringstream to capture output
    std::stringstream buffer;
    std::streambuf* old = std::cout.rdbuf(buffer.rdbuf());

    array.PrintAreas();

    std::cout.rdbuf(old); // Restore cout

    std::string output = buffer.str();
    EXPECT_TRUE(output.empty()); // No output for empty array
}

// Test PrintAreas with mixed figures
TEST_F(ArrayFigurePointerTest, PrintAreasMixedFigures) {
    lib::array::ArrayFigurePointer array = {pentagon2, rhombus2, trapezoid2};

    // Redirect cout to stringstream to capture output
    std::stringstream buffer;
    std::streambuf* old = std::cout.rdbuf(buffer.rdbuf());

    array.PrintAreas();

    std::cout.rdbuf(old); // Restore cout

    std::string output = buffer.str();

    // Should contain area information for all figures
    EXPECT_FALSE(output.empty());
    EXPECT_NE(output.find("Figure 0 area:"), std::string::npos);
    EXPECT_NE(output.find("Figure 1 area:"), std::string::npos);
    EXPECT_NE(output.find("Figure 2 area:"), std::string::npos);

    // All areas should be positive
    double area0 = static_cast<double>(*pentagon2);
    double area1 = static_cast<double>(*rhombus2);
    double area2 = static_cast<double>(*trapezoid2);

    EXPECT_GT(area0, 0);
    EXPECT_GT(area1, 0);
    EXPECT_GT(area2, 0);
}

// Test GetTotalArea with empty array
TEST_F(ArrayFigurePointerTest, GetTotalAreaEmpty) {
    lib::array::ArrayFigurePointer array;

    double total_area = array.GetTotalArea();
    EXPECT_DOUBLE_EQ(total_area, 0.0);
}

// Test GetTotalArea with single figure
TEST_F(ArrayFigurePointerTest, GetTotalAreaSingleFigure) {
    lib::array::ArrayFigurePointer array = {pentagon1};

    double expected_area = static_cast<double>(*pentagon1);
    double total_area = array.GetTotalArea();

    EXPECT_DOUBLE_EQ(total_area, expected_area);
    EXPECT_GT(total_area, 0);
}

// Test GetTotalArea with multiple figures of same type
TEST_F(ArrayFigurePointerTest, GetTotalAreaMultipleSameType) {
    lib::array::ArrayFigurePointer array = {pentagon1, pentagon2};

    double expected_area =
        static_cast<double>(*pentagon1) + static_cast<double>(*pentagon2);
    double total_area = array.GetTotalArea();

    EXPECT_DOUBLE_EQ(total_area, expected_area);
    EXPECT_GT(total_area, 0);
}

// Test GetTotalArea with mixed figure types
TEST_F(ArrayFigurePointerTest, GetTotalAreaMixedFigures) {
    lib::array::ArrayFigurePointer array = {pentagon1, rhombus1, trapezoid1};

    double expected_area = static_cast<double>(*pentagon1) +
                           static_cast<double>(*rhombus1) +
                           static_cast<double>(*trapezoid1);
    double total_area = array.GetTotalArea();

    EXPECT_NEAR(total_area, expected_area, 1e-10);
    EXPECT_GT(total_area, 0);
}

// Test GetTotalArea with all figure types
TEST_F(ArrayFigurePointerTest, GetTotalAreaAllFigureTypes) {
    lib::array::ArrayFigurePointer array = {pentagon1, pentagon2,  rhombus1,
                                            rhombus2,  trapezoid1, trapezoid2};

    double expected_area =
        static_cast<double>(*pentagon1) + static_cast<double>(*pentagon2) +
        static_cast<double>(*rhombus1) + static_cast<double>(*rhombus2) +
        static_cast<double>(*trapezoid1) + static_cast<double>(*trapezoid2);
    double total_area = array.GetTotalArea();

    EXPECT_NEAR(total_area, expected_area, 1e-10);
    EXPECT_GT(total_area, 0);
}

// Test that GetTotalArea works after PushBack operations
TEST_F(ArrayFigurePointerTest, GetTotalAreaAfterPushBack) {
    lib::array::ArrayFigurePointer array;

    // Initially empty
    EXPECT_DOUBLE_EQ(array.GetTotalArea(), 0.0);

    // Add figures one by one and verify total area
    array.PushBack(pentagon1);
    double area1 = static_cast<double>(*pentagon1);
    EXPECT_DOUBLE_EQ(array.GetTotalArea(), area1);

    array.PushBack(rhombus1);
    double area2 = area1 + static_cast<double>(*rhombus1);
    EXPECT_DOUBLE_EQ(array.GetTotalArea(), area2);

    array.PushBack(trapezoid1);
    double area3 = area2 + static_cast<double>(*trapezoid1);
    EXPECT_DOUBLE_EQ(array.GetTotalArea(), area3);
}

// Test that GetTotalArea works after PopBack operations
TEST_F(ArrayFigurePointerTest, GetTotalAreaAfterPopBack) {
    lib::array::ArrayFigurePointer array = {pentagon1, rhombus1, trapezoid1};

    double initial_area = static_cast<double>(*pentagon1) +
                          static_cast<double>(*rhombus1) +
                          static_cast<double>(*trapezoid1);
    EXPECT_DOUBLE_EQ(array.GetTotalArea(), initial_area);

    // Remove one figure
    array.PopBack();
    double area_after_pop =
        static_cast<double>(*pentagon1) + static_cast<double>(*rhombus1);
    EXPECT_DOUBLE_EQ(array.GetTotalArea(), area_after_pop);

    // Remove another figure
    array.PopBack();
    double final_area = static_cast<double>(*pentagon1);
    EXPECT_DOUBLE_EQ(array.GetTotalArea(), final_area);

    // Remove last figure
    array.PopBack();
    EXPECT_DOUBLE_EQ(array.GetTotalArea(), 0.0);
}

// Test that GetTotalArea works after Clear operation
TEST_F(ArrayFigurePointerTest, GetTotalAreaAfterClear) {
    lib::array::ArrayFigurePointer array = {pentagon1, rhombus1, trapezoid1};

    // Should have positive area
    double total_area = array.GetTotalArea();
    EXPECT_GT(total_area, 0);

    // Clear the array
    array.Clear();

    // Area should be zero after clear
    EXPECT_DOUBLE_EQ(array.GetTotalArea(), 0.0);
}

// Test that GetTotalArea works after Resize operation
TEST_F(ArrayFigurePointerTest, GetTotalAreaAfterResize) {
    lib::array::ArrayFigurePointer array = {pentagon1, rhombus1};

    double initial_area =
        static_cast<double>(*pentagon1) + static_cast<double>(*rhombus1);
    EXPECT_DOUBLE_EQ(array.GetTotalArea(), initial_area);

    // Resize to larger size with new figures
    array.Resize(4, trapezoid1);
    double expected_area =
        static_cast<double>(*pentagon1) + static_cast<double>(*rhombus1) +
        2 * static_cast<double>(*trapezoid1); // Two new trapezoids

    EXPECT_NEAR(array.GetTotalArea(), expected_area, 1e-10);
}

// Test PrintCentroids and PrintAreas with const ArrayFigurePointer
TEST_F(ArrayFigurePointerTest, ConstArrayPrintFunctions) {
    lib::array::ArrayFigurePointer non_const_array = {pentagon1, rhombus1};
    const lib::array::ArrayFigurePointer& const_array = non_const_array;

    // Both should compile and work for const objects
    std::stringstream buffer1;
    std::streambuf* old1 = std::cout.rdbuf(buffer1.rdbuf());
    const_array.PrintCentroids();
    std::cout.rdbuf(old1);
    EXPECT_FALSE(buffer1.str().empty());

    std::stringstream buffer2;
    std::streambuf* old2 = std::cout.rdbuf(buffer2.rdbuf());
    const_array.PrintAreas();
    std::cout.rdbuf(old2);
    EXPECT_FALSE(buffer2.str().empty());

    // GetTotalArea should work on const objects
    double total_area = const_array.GetTotalArea();
    EXPECT_GT(total_area, 0);
}

// Test that functions work correctly with zero-area figures
TEST_F(ArrayFigurePointerTest, ZeroAreaFigures) {
    // Create a very small pentagon (approaching zero area)
    lib::geometry::Pentagon* small_pentagon = new lib::geometry::Pentagon(
        lib::geometry::Vec2(0, 0), lib::geometry::Vec2(0.0001, 0));

    // Create a flat rhombus (zero area)
    lib::geometry::Rhombus* flat_rhombus = new lib::geometry::Rhombus(
        lib::geometry::Vec2(0, 0), lib::geometry::Vec2(1, 0),
        0.0 // Zero angle = zero area
    );

    lib::array::ArrayFigurePointer array = {small_pentagon, flat_rhombus};

    // Total area should be very small
    double total_area = array.GetTotalArea();
    EXPECT_GE(total_area, 0);
    EXPECT_LT(total_area, 0.01);

    // Clean up
    delete small_pentagon;
    delete flat_rhombus;
}

// Test memory management doesn't affect Figure-specific functions
TEST_F(ArrayFigurePointerTest, MemoryManagementIntegration) {
    // Test that array operations don't affect the underlying figures
    lib::array::ArrayFigurePointer array;

    // Store initial areas
    double pentagon_area = static_cast<double>(*pentagon1);
    double rhombus_area = static_cast<double>(*rhombus1);

    array.PushBack(pentagon1);
    array.PushBack(rhombus1);

    // Areas should remain the same
    EXPECT_DOUBLE_EQ(static_cast<double>(*pentagon1), pentagon_area);
    EXPECT_DOUBLE_EQ(static_cast<double>(*rhombus1), rhombus_area);

    // Total area should be sum
    EXPECT_DOUBLE_EQ(array.GetTotalArea(), pentagon_area + rhombus_area);

    // Clear shouldn't affect the figures themselves
    array.Clear();
    EXPECT_DOUBLE_EQ(static_cast<double>(*pentagon1), pentagon_area);
    EXPECT_DOUBLE_EQ(static_cast<double>(*rhombus1), rhombus_area);
}
