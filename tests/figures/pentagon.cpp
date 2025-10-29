#include <cmath>
#include <sstream>

#include <gtest/gtest.h>

#include "pentagon.hpp"

class PentagonTest : public ::testing::Test {
  protected:
    void SetUp() override {
        // Common test data
        origin = lib::geometry::Vec2(0, 0);
        unit_x = lib::geometry::Vec2(1, 0);
        unit_y = lib::geometry::Vec2(0, 1);
    }

    lib::geometry::Vec2 origin;
    lib::geometry::Vec2 unit_x;
    lib::geometry::Vec2 unit_y;
};

// Test default constructor
TEST_F(PentagonTest, DefaultConstructor) {
    lib::geometry::Pentagon pent;

    // Default constructed pentagon should have valid but unspecified points
    // We can at least check that it doesn't crash and centroid is calculable
    lib::geometry::Vec2 centroid = pent.Centroid();
    SUCCEED(); // Just verify it doesn't throw
}

// Test constructor with radius and guiding vectors
TEST_F(PentagonTest, ConstructorWithVectors) {
    lib::geometry::Vec2 radius_vector(2, 3);
    lib::geometry::Vec2 guiding_vector(1, 0); // Horizontal vector of length 1

    lib::geometry::Pentagon pent(radius_vector, guiding_vector);

    // Test that the pentagon can be converted to double (area)
    double area = static_cast<double>(pent);
    EXPECT_GT(area, 0); // Area should be positive

    // Test centroid calculation
    lib::geometry::Vec2 centroid = pent.Centroid();
    // For a regular pentagon, centroid should be calculable
}

// Test pentagon with vertical guiding vector
TEST_F(PentagonTest, VerticalGuidingVector) {
    lib::geometry::Vec2 radius_vector(0, 0);
    lib::geometry::Vec2 guiding_vector(0, 2); // Vertical vector of length 2

    lib::geometry::Pentagon pent(radius_vector, guiding_vector);

    double area = static_cast<double>(pent);
    EXPECT_GT(area, 0);
}

// Test pentagon with diagonal guiding vector
TEST_F(PentagonTest, DiagonalGuidingVector) {
    lib::geometry::Vec2 radius_vector(1, 1);
    lib::geometry::Vec2 guiding_vector(1, 1); // 45-degree vector

    lib::geometry::Pentagon pent(radius_vector, guiding_vector);

    double area = static_cast<double>(pent);
    EXPECT_GT(area, 0);
}

// Test pentagon at origin
TEST_F(PentagonTest, OriginPentagon) {
    lib::geometry::Vec2 radius_vector(0, 0);
    lib::geometry::Vec2 guiding_vector(1, 0);

    lib::geometry::Pentagon pent(radius_vector, guiding_vector);

    double area = static_cast<double>(pent);
    EXPECT_GT(area, 0);

    lib::geometry::Vec2 centroid = pent.Centroid();
    // Centroid should not be at origin for a regular pentagon starting at
    // origin
}

// Test area calculation consistency
TEST_F(PentagonTest, AreaConsistency) {
    lib::geometry::Vec2 radius_vector(0, 0);
    lib::geometry::Vec2 guiding_vector1(1, 0);
    lib::geometry::Vec2 guiding_vector2(2, 0); // Double the length

    lib::geometry::Pentagon pent1(radius_vector, guiding_vector1);
    lib::geometry::Pentagon pent2(radius_vector, guiding_vector2);

    double area1 = static_cast<double>(pent1);
    double area2 = static_cast<double>(pent2);

    // Area should scale with the square of the side length
    // For regular pentagon: area = (1/4) * sqrt(5*(5+2*sqrt(5))) * side²
    // So doubling side length should quadruple area
    EXPECT_NEAR(area2 / area1, 4.0, 0.1); // Allow small floating point error
}

// Test stream input operator
TEST_F(PentagonTest, StreamInput) {
    std::istringstream iss(
        "2.0 3.0 1.0 0.0"); // radius_vector(2,3), guiding_vector(1,0)
    lib::geometry::Pentagon pent;

    iss >> pent;

    EXPECT_FALSE(iss.fail()); // Reading should succeed
    double area = static_cast<double>(pent);
    EXPECT_GT(area, 0);
}

// Test stream input with invalid data
TEST_F(PentagonTest, StreamInputInvalid) {
    std::istringstream iss("invalid data");
    lib::geometry::Pentagon pent;

    iss >> pent;

    EXPECT_TRUE(iss.fail()); // Reading should fail with invalid data
}

// Test stream output operator
TEST_F(PentagonTest, StreamOutput) {
    lib::geometry::Vec2 radius_vector(1, 2);
    lib::geometry::Vec2 guiding_vector(3, 4);
    lib::geometry::Pentagon pent(radius_vector, guiding_vector);

    std::ostringstream oss;
    oss << pent;

    std::string output = oss.str();
    EXPECT_FALSE(output.empty()); // Output should not be empty
}

// Test multiple pentagons with same parameters have same area
TEST_F(PentagonTest, ConsistencySameParameters) {
    lib::geometry::Vec2 radius_vector(5, 5);
    lib::geometry::Vec2 guiding_vector(2, 0);

    lib::geometry::Pentagon pent1(radius_vector, guiding_vector);
    lib::geometry::Pentagon pent2(radius_vector, guiding_vector);

    double area1 = static_cast<double>(pent1);
    double area2 = static_cast<double>(pent2);

    EXPECT_DOUBLE_EQ(area1, area2); // Areas should be exactly equal
}

// Test pentagon with very small side length
TEST_F(PentagonTest, VerySmallPentagon) {
    lib::geometry::Vec2 radius_vector(0, 0);
    lib::geometry::Vec2 guiding_vector(0.001, 0); // Very small side

    lib::geometry::Pentagon pent(radius_vector, guiding_vector);

    double area = static_cast<double>(pent);
    EXPECT_GE(area, 0);     // Area should be non-negative
    EXPECT_LT(area, 0.001); // Area should be very small
}

// Test pentagon with different orientations
TEST_F(PentagonTest, DifferentOrientations) {
    // Test multiple orientations
    std::vector<lib::geometry::Vec2> guiding_vectors = {
        lib::geometry::Vec2(1, 0),  // Right
        lib::geometry::Vec2(0, 1),  // Up
        lib::geometry::Vec2(-1, 0), // Left
        lib::geometry::Vec2(0, -1), // Down
        lib::geometry::Vec2(1, 1),  // Diagonal
        lib::geometry::Vec2(1, -1)  // Other diagonal
    };

    lib::geometry::Vec2 radius_vector(0, 0);

    for (const auto& guiding_vector : guiding_vectors) {
        lib::geometry::Pentagon pent(radius_vector, guiding_vector);
        double area = static_cast<double>(pent);
        EXPECT_GT(area, 0); // All should have positive area

        lib::geometry::Vec2 centroid = pent.Centroid();
        // Centroid should be calculable for all orientations
    }
}

// Test that pentagon implements Figure interface
TEST_F(PentagonTest, FigureInterface) {
    lib::geometry::Vec2 radius_vector(1, 1);
    lib::geometry::Vec2 guiding_vector(2, 0);
    lib::geometry::Pentagon pent(radius_vector, guiding_vector);

    // Test that Pentagon can be used as Figure through base class pointers
    lib::geometry::Figure* figure_ptr = &pent;

    // Should be able to call virtual methods
    double area = static_cast<double>(*figure_ptr);
    EXPECT_GT(area, 0);

    lib::geometry::Vec2 centroid = figure_ptr->Centroid();
    SUCCEED(); // Verify call doesn't throw
}

// Test centroid calculation for known case
TEST_F(PentagonTest, CentroidCalculation) {
    // For a regular pentagon centered at origin with radius vector at one
    // vertex, the centroid should be offset from that vertex
    lib::geometry::Vec2 radius_vector(1, 0);  // On x-axis
    lib::geometry::Vec2 guiding_vector(0, 1); // Pointing up

    lib::geometry::Pentagon pent(radius_vector, guiding_vector);

    lib::geometry::Vec2 centroid = pent.Centroid();

    // Centroid should not be the same as the radius vector
    EXPECT_NE(centroid.x, radius_vector.x);
    EXPECT_NE(centroid.y, radius_vector.y);

    // Centroid should have finite coordinates
    EXPECT_TRUE(std::isfinite(centroid.x));
    EXPECT_TRUE(std::isfinite(centroid.y));
}

// Test edge case: zero-length guiding vector
TEST_F(PentagonTest, ZeroLengthGuidingVector) {
    lib::geometry::Vec2 radius_vector(0, 0);
    lib::geometry::Vec2 guiding_vector(0, 0); // Zero vector

    // Behavior is undefined by the interface, but we test it doesn't crash
    lib::geometry::Pentagon pent(radius_vector, guiding_vector);

    double area = static_cast<double>(pent);
    // Area could be zero or implementation-defined
}

// Test negative coordinates
TEST_F(PentagonTest, NegativeCoordinates) {
    lib::geometry::Vec2 radius_vector(-2, -3);
    lib::geometry::Vec2 guiding_vector(-1, 0);

    lib::geometry::Pentagon pent(radius_vector, guiding_vector);

    double area = static_cast<double>(pent);
    EXPECT_GT(area, 0); // Area should still be positive

    lib::geometry::Vec2 centroid = pent.Centroid();
    EXPECT_TRUE(std::isfinite(centroid.x));
    EXPECT_TRUE(std::isfinite(centroid.y));
}

// Test large values
TEST_F(PentagonTest, LargeValues) {
    lib::geometry::Vec2 radius_vector(1000, 2000);
    lib::geometry::Vec2 guiding_vector(100, 0);

    lib::geometry::Pentagon pent(radius_vector, guiding_vector);

    double area = static_cast<double>(pent);
    EXPECT_GT(area, 0);

    lib::geometry::Vec2 centroid = pent.Centroid();
    EXPECT_TRUE(std::isfinite(centroid.x));
    EXPECT_TRUE(std::isfinite(centroid.y));
}
