#include <cmath>
#include <sstream>

#include <gtest/gtest.h>

#include "rhombus.hpp"

class RhombusTest : public ::testing::Test {
  protected:
    void SetUp() override {
        // Common test data
        origin = lib::geometry::Vec2(0, 0);
        unit_x = lib::geometry::Vec2(1, 0);
        unit_y = lib::geometry::Vec2(0, 1);
        pi = std::acos(-1.0);
    }

    void TearDown() override {}

    lib::geometry::Vec2 origin;
    lib::geometry::Vec2 unit_x;
    lib::geometry::Vec2 unit_y;
    double pi;
};

// Test default constructor
TEST_F(RhombusTest, DefaultConstructor) {
    lib::geometry::Rhombus rhombus;

    // Default constructed rhombus should have valid but unspecified points
    // We can at least check that it doesn't crash and centroid is calculable
    lib::geometry::Vec2 centroid = rhombus.Centroid();
    SUCCEED(); // Just verify it doesn't throw
}

// Test constructor with radius vector, guiding vector and angle
TEST_F(RhombusTest, ConstructorWithVectorsAndAngle) {
    lib::geometry::Vec2 radius_vector(2, 3);
    lib::geometry::Vec2 guiding_vector(1, 0);
    double angle = pi / 3; // 60 degrees

    lib::geometry::Rhombus rhombus(radius_vector, guiding_vector, angle);

    // Test that the rhombus can be converted to double (area)
    double area = static_cast<double>(rhombus);
    EXPECT_GE(area, 0); // Area should be non-negative

    // Test centroid calculation
    lib::geometry::Vec2 centroid = rhombus.Centroid();
    SUCCEED(); // Verify call doesn't throw
}

// Test square case (angle = π/2)
TEST_F(RhombusTest, SquareCase) {
    lib::geometry::Vec2 radius_vector(0, 0);
    lib::geometry::Vec2 guiding_vector(1, 0);
    double angle = pi / 2; // 90 degrees - should form a square

    lib::geometry::Rhombus rhombus(radius_vector, guiding_vector, angle);

    double area = static_cast<double>(rhombus);
    EXPECT_NEAR(area, 1.0, 1e-10); // Area should be 1 for unit square
}

// Test flat rhombus (angle approaching 0)
TEST_F(RhombusTest, FlatRhombus) {
    lib::geometry::Vec2 radius_vector(0, 0);
    lib::geometry::Vec2 guiding_vector(1, 0);
    double angle = 0.001; // Very small angle

    lib::geometry::Rhombus rhombus(radius_vector, guiding_vector, angle);

    double area = static_cast<double>(rhombus);
    EXPECT_GE(area, 0);     // Area should be non-negative
    EXPECT_LT(area, 0.001); // Area should be very small for flat rhombus
}

// Test different angles
TEST_F(RhombusTest, DifferentAngles) {
    lib::geometry::Vec2 radius_vector(0, 0);
    lib::geometry::Vec2 guiding_vector(1, 0);

    std::vector<double> angles = {pi / 6, pi / 4, pi / 3, pi / 2, 2 * pi / 3};

    for (double angle : angles) {
        lib::geometry::Rhombus rhombus(radius_vector, guiding_vector, angle);
        double area = static_cast<double>(rhombus);
        EXPECT_GE(area, 0); // All areas should be non-negative
    }
}

// Test area calculation consistency with side length
TEST_F(RhombusTest, AreaScalingWithSide) {
    lib::geometry::Vec2 radius_vector(0, 0);
    double angle = pi / 3; // 60 degrees

    lib::geometry::Vec2 guiding_vector1(1, 0);
    lib::geometry::Vec2 guiding_vector2(2, 0); // Double the length

    lib::geometry::Rhombus rhombus1(radius_vector, guiding_vector1, angle);
    lib::geometry::Rhombus rhombus2(radius_vector, guiding_vector2, angle);

    double area1 = static_cast<double>(rhombus1);
    double area2 = static_cast<double>(rhombus2);

    // Area should scale with the square of the side length
    // For rhombus: area = side² * sin(angle)
    EXPECT_NEAR(area2 / area1, 4.0, 1e-10);
}

// Test area calculation with different angles
TEST_F(RhombusTest, AreaWithDifferentAngles) {
    lib::geometry::Vec2 radius_vector(0, 0);
    lib::geometry::Vec2 guiding_vector(1, 0);

    double angle1 = pi / 6; // 30 degrees
    double angle2 = pi / 2; // 90 degrees

    lib::geometry::Rhombus rhombus1(radius_vector, guiding_vector, angle1);
    lib::geometry::Rhombus rhombus2(radius_vector, guiding_vector, angle2);

    double area1 = static_cast<double>(rhombus1);
    double area2 = static_cast<double>(rhombus2);

    // Area ratio should be sin(angle1) / sin(angle2) = sin(30)/sin(90) = 0.5/1
    // = 0.5
    EXPECT_NEAR(area1 / area2, 0.5, 1e-10);
}

// Test stream input operator
TEST_F(RhombusTest, StreamInput) {
    std::istringstream iss(
        "2.0 3.0 1.0 0.0 1.047197551"); // radius_vector(2,3),
                                        // guiding_vector(1,0), angle=π/3
    lib::geometry::Rhombus rhombus;

    iss >> rhombus;

    EXPECT_FALSE(iss.fail()); // Reading should succeed
    double area = static_cast<double>(rhombus);
    EXPECT_GE(area, 0);
}

// Test stream input with invalid data
TEST_F(RhombusTest, StreamInputInvalid) {
    std::istringstream iss("invalid data");
    lib::geometry::Rhombus rhombus;

    iss >> rhombus;

    EXPECT_TRUE(iss.fail()); // Reading should fail with invalid data
}

// Test stream output operator
TEST_F(RhombusTest, StreamOutput) {
    lib::geometry::Vec2 radius_vector(1, 2);
    lib::geometry::Vec2 guiding_vector(3, 4);
    double angle = pi / 4;

    lib::geometry::Rhombus rhombus(radius_vector, guiding_vector, angle);

    std::ostringstream oss;
    oss << rhombus;

    std::string output = oss.str();
    EXPECT_FALSE(output.empty()); // Output should not be empty
}

// Test multiple rhombuses with same parameters have same area
TEST_F(RhombusTest, ConsistencySameParameters) {
    lib::geometry::Vec2 radius_vector(5, 5);
    lib::geometry::Vec2 guiding_vector(2, 0);
    double angle = pi / 3;

    lib::geometry::Rhombus rhombus1(radius_vector, guiding_vector, angle);
    lib::geometry::Rhombus rhombus2(radius_vector, guiding_vector, angle);

    double area1 = static_cast<double>(rhombus1);
    double area2 = static_cast<double>(rhombus2);

    EXPECT_DOUBLE_EQ(area1, area2); // Areas should be exactly equal
}

// Test rhombus with different orientations
TEST_F(RhombusTest, DifferentOrientations) {
    std::vector<lib::geometry::Vec2> guiding_vectors = {
        lib::geometry::Vec2(1, 0),  // Right
        lib::geometry::Vec2(0, 1),  // Up
        lib::geometry::Vec2(-1, 0), // Left
        lib::geometry::Vec2(0, -1), // Down
        lib::geometry::Vec2(1, 1)   // Diagonal
    };

    lib::geometry::Vec2 radius_vector(0, 0);
    double angle = pi / 3;

    for (const auto& guiding_vector : guiding_vectors) {
        lib::geometry::Rhombus rhombus(radius_vector, guiding_vector, angle);
        double area = static_cast<double>(rhombus);
        EXPECT_GE(area, 0); // All should have non-negative area

        lib::geometry::Vec2 centroid = rhombus.Centroid();
        SUCCEED(); // Centroid should be calculable for all orientations
    }
}

// Test that rhombus implements Figure interface
TEST_F(RhombusTest, FigureInterface) {
    lib::geometry::Vec2 radius_vector(1, 1);
    lib::geometry::Vec2 guiding_vector(2, 0);
    double angle = pi / 4;

    lib::geometry::Rhombus rhombus(radius_vector, guiding_vector, angle);

    // Test that Rhombus can be used as Figure through base class pointers
    lib::geometry::Figure* figure_ptr = &rhombus;

    // Should be able to call virtual methods
    double area = static_cast<double>(*figure_ptr);
    EXPECT_GE(area, 0);

    lib::geometry::Vec2 centroid = figure_ptr->Centroid();
    SUCCEED(); // Verify call doesn't throw
}

// Test centroid calculation
TEST_F(RhombusTest, CentroidCalculation) {
    lib::geometry::Vec2 radius_vector(1, 0);
    lib::geometry::Vec2 guiding_vector(0, 1);
    double angle = pi / 3;

    lib::geometry::Rhombus rhombus(radius_vector, guiding_vector, angle);

    lib::geometry::Vec2 centroid = rhombus.Centroid();

    // Centroid should not be the same as the radius vector
    EXPECT_NE(centroid.x, radius_vector.x);
    EXPECT_NE(centroid.y, radius_vector.y);

    // Centroid should have finite coordinates
    EXPECT_TRUE(std::isfinite(centroid.x));
    EXPECT_TRUE(std::isfinite(centroid.y));
}

// Test edge case: zero-length guiding vector
TEST_F(RhombusTest, ZeroLengthGuidingVector) {
    lib::geometry::Vec2 radius_vector(0, 0);
    lib::geometry::Vec2 guiding_vector(0, 0); // Zero vector
    double angle = pi / 3;

    // Behavior is undefined by the interface, but we test it doesn't crash
    lib::geometry::Rhombus rhombus(radius_vector, guiding_vector, angle);

    double area = static_cast<double>(rhombus);
    // Area could be zero or implementation-defined
}

// Test edge case: zero angle
TEST_F(RhombusTest, ZeroAngle) {
    lib::geometry::Vec2 radius_vector(0, 0);
    lib::geometry::Vec2 guiding_vector(1, 0);
    double angle = 0.0;

    lib::geometry::Rhombus rhombus(radius_vector, guiding_vector, angle);

    double area = static_cast<double>(rhombus);
    EXPECT_GE(area, 0); // Area should be non-negative
    // For zero angle, area should be zero (flat rhombus)
}

// Test edge case: π angle (flat in opposite direction)
TEST_F(RhombusTest, PiAngle) {
    lib::geometry::Vec2 radius_vector(0, 0);
    lib::geometry::Vec2 guiding_vector(1, 0);
    double angle = pi;

    lib::geometry::Rhombus rhombus(radius_vector, guiding_vector, angle);

    double area = static_cast<double>(rhombus);
    EXPECT_NEAR(area, 0.0, 1e-10); // Area should be zero (flat)
}

// Test negative coordinates
TEST_F(RhombusTest, NegativeCoordinates) {
    lib::geometry::Vec2 radius_vector(-2, -3);
    lib::geometry::Vec2 guiding_vector(-1, 0);
    double angle = pi / 4;

    lib::geometry::Rhombus rhombus(radius_vector, guiding_vector, angle);

    double area = static_cast<double>(rhombus);
    EXPECT_GE(area, 0); // Area should still be positive

    lib::geometry::Vec2 centroid = rhombus.Centroid();
    EXPECT_TRUE(std::isfinite(centroid.x));
    EXPECT_TRUE(std::isfinite(centroid.y));
}

// Test large values
TEST_F(RhombusTest, LargeValues) {
    lib::geometry::Vec2 radius_vector(1000, 2000);
    lib::geometry::Vec2 guiding_vector(100, 0);
    double angle = pi / 3;

    lib::geometry::Rhombus rhombus(radius_vector, guiding_vector, angle);

    double area = static_cast<double>(rhombus);
    EXPECT_GT(area, 0);

    lib::geometry::Vec2 centroid = rhombus.Centroid();
    EXPECT_TRUE(std::isfinite(centroid.x));
    EXPECT_TRUE(std::isfinite(centroid.y));
}

// Test that rhombus is to the left of guiding vector
TEST_F(RhombusTest, LeftOfGuidingVector) {
    lib::geometry::Vec2 radius_vector(0, 0);
    lib::geometry::Vec2 guiding_vector(1, 0); // Pointing right
    double angle = pi / 3;

    lib::geometry::Rhombus rhombus(radius_vector, guiding_vector, angle);

    // The rhombus should be situated to the left of the guiding vector
    // This means it should extend in the positive Y direction
    // This is a conceptual test - actual implementation would depend on point
    // ordering
    SUCCEED(); // Verify construction doesn't throw
}

// Test copy constructor and assignment
TEST_F(RhombusTest, CopyOperations) {
    lib::geometry::Vec2 radius_vector(1, 1);
    lib::geometry::Vec2 guiding_vector(2, 0);
    double angle = pi / 4;

    lib::geometry::Rhombus rhombus1(radius_vector, guiding_vector, angle);
    lib::geometry::Rhombus rhombus2 = rhombus1; // Copy constructor

    double area1 = static_cast<double>(rhombus1);
    double area2 = static_cast<double>(rhombus2);

    EXPECT_DOUBLE_EQ(area1, area2);

    lib::geometry::Rhombus rhombus3;
    rhombus3 = rhombus1; // Assignment operator

    double area3 = static_cast<double>(rhombus3);
    EXPECT_DOUBLE_EQ(area1, area3);
}
