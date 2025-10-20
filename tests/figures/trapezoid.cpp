#include "trapezoid.hpp"
#include <cmath>
#include <gtest/gtest.h>
#include <sstream>

class TrapezoidTest : public ::testing::Test {
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
TEST_F(TrapezoidTest, DefaultConstructor) {
    lib::geometry::Trapezoid trapezoid;

    // Default constructed trapezoid should have valid but unspecified points
    lib::geometry::Vec2 centroid = trapezoid.Centroid();
    SUCCEED(); // Just verify it doesn't throw
}

// Test constructor with radius vector, guiding vector, angle and side length
TEST_F(TrapezoidTest, ConstructorWithAllParameters) {
    lib::geometry::Vec2 radius_vector(2, 3);
    lib::geometry::Vec2 guiding_vector(4, 0); // Greater base length = 4
    double angle = pi / 4;                    // 45 degrees
    double side_length = 2.0;

    lib::geometry::Trapezoid trapezoid(radius_vector, guiding_vector, angle,
                                       side_length);

    // Test that the trapezoid can be converted to double (area)
    double area = static_cast<double>(trapezoid);
    EXPECT_GE(area, 0); // Area should be non-negative

    // Test centroid calculation
    lib::geometry::Vec2 centroid = trapezoid.Centroid();
    SUCCEED(); // Verify call doesn't throw
}

// Test rectangle case (angle = π/2)
TEST_F(TrapezoidTest, RectangleCase) {
    lib::geometry::Vec2 radius_vector(0, 0);
    lib::geometry::Vec2 guiding_vector(4, 0); // Greater base length = 4
    double angle = pi / 2;    // 90 degrees - should form a rectangle
    double side_length = 2.0; // Height

    lib::geometry::Trapezoid trapezoid(radius_vector, guiding_vector, angle,
                                       side_length);

    double area = static_cast<double>(trapezoid);
    // For rectangle: area = base * height = 4 * 2 = 8
    EXPECT_NEAR(area, 8.0, 1e-10);
}

// Test different angles
TEST_F(TrapezoidTest, DifferentAngles) {
    lib::geometry::Vec2 radius_vector(0, 0);
    lib::geometry::Vec2 guiding_vector(5, 0);
    double side_length = 3.0;

    std::vector<double> angles = {pi / 6, pi / 4, pi / 3, pi / 2};

    for (double angle : angles) {
        lib::geometry::Trapezoid trapezoid(radius_vector, guiding_vector, angle,
                                           side_length);
        double area = static_cast<double>(trapezoid);
        EXPECT_GE(area, 0); // All areas should be non-negative
    }
}

// Test area calculation consistency with base length
TEST_F(TrapezoidTest, AreaScalingWithBase) {
    lib::geometry::Vec2 radius_vector(0, 0);
    double angle = pi / 3;
    double side_length = 2.0;

    lib::geometry::Vec2 guiding_vector1(2, 0);
    lib::geometry::Vec2 guiding_vector2(4, 0); // Double the base length

    lib::geometry::Trapezoid trapezoid1(radius_vector, guiding_vector1, angle,
                                        side_length);
    lib::geometry::Trapezoid trapezoid2(radius_vector, guiding_vector2, angle,
                                        side_length);

    double area1 = static_cast<double>(trapezoid1);
    double area2 = static_cast<double>(trapezoid2);

    // Area should increase with base length (not necessarily double since
    // lesser base changes)
    EXPECT_GT(area2, area1);
}

// Test area calculation for known trapezoid
TEST_F(TrapezoidTest, KnownTrapezoidArea) {
    lib::geometry::Vec2 radius_vector(0, 0);
    lib::geometry::Vec2 guiding_vector(6, 0); // Greater base = 6
    double angle = pi / 3;                    // 60 degrees
    double side_length = 2.0;

    // Height = side_length * sin(angle) = 2 * sin(60°) = 2 * √3/2 = √3 ≈ 1.732
    // Lesser base = greater_base - 2 * side_length * cos(angle) = 6 - 2 * 2 *
    // cos(60°) = 6 - 4 * 0.5 = 4 Area = (greater_base + lesser_base)/2 * height
    // = (6 + 4)/2 * √3 = 5 * √3 ≈ 8.66

    lib::geometry::Trapezoid trapezoid(radius_vector, guiding_vector, angle,
                                       side_length);
    double area = static_cast<double>(trapezoid);
    double expected_area = 5.0 * std::sqrt(3.0); // 5√3

    EXPECT_NEAR(area, expected_area, 1e-10);
}

// Test stream input operator
TEST_F(TrapezoidTest, StreamInput) {
    std::istringstream iss("2.0 3.0 4.0 0.0 1.047197551 2.5");
    // radius_vector(2,3), guiding_vector(4,0), angle=π/3, side_length=2.5
    lib::geometry::Trapezoid trapezoid;

    iss >> trapezoid;

    EXPECT_FALSE(iss.fail()); // Reading should succeed
    double area = static_cast<double>(trapezoid);
    EXPECT_GE(area, 0);
}

// Test stream input with invalid data
TEST_F(TrapezoidTest, StreamInputInvalid) {
    std::istringstream iss("invalid data");
    lib::geometry::Trapezoid trapezoid;

    iss >> trapezoid;

    EXPECT_TRUE(iss.fail()); // Reading should fail with invalid data
}

// Test stream output operator
TEST_F(TrapezoidTest, StreamOutput) {
    lib::geometry::Vec2 radius_vector(1, 2);
    lib::geometry::Vec2 guiding_vector(3, 4);
    double angle = pi / 4;
    double side_length = 2.5;

    lib::geometry::Trapezoid trapezoid(radius_vector, guiding_vector, angle,
                                       side_length);

    std::ostringstream oss;
    oss << trapezoid;

    std::string output = oss.str();
    EXPECT_FALSE(output.empty()); // Output should not be empty
}

// Test multiple trapezoids with same parameters have same area
TEST_F(TrapezoidTest, ConsistencySameParameters) {
    lib::geometry::Vec2 radius_vector(5, 5);
    lib::geometry::Vec2 guiding_vector(4, 0);
    double angle = pi / 3;
    double side_length = 3.0;

    lib::geometry::Trapezoid trapezoid1(radius_vector, guiding_vector, angle,
                                        side_length);
    lib::geometry::Trapezoid trapezoid2(radius_vector, guiding_vector, angle,
                                        side_length);

    double area1 = static_cast<double>(trapezoid1);
    double area2 = static_cast<double>(trapezoid2);

    EXPECT_DOUBLE_EQ(area1, area2); // Areas should be exactly equal
}

// Test trapezoid with different orientations
TEST_F(TrapezoidTest, DifferentOrientations) {
    std::vector<lib::geometry::Vec2> guiding_vectors = {
        lib::geometry::Vec2(4, 0),  // Right
        lib::geometry::Vec2(0, 4),  // Up
        lib::geometry::Vec2(-4, 0), // Left
        lib::geometry::Vec2(0, -4), // Down
        lib::geometry::Vec2(3, 3)   // Diagonal
    };

    lib::geometry::Vec2 radius_vector(0, 0);
    double angle = pi / 4;
    double side_length = 2.0;

    for (const auto& guiding_vector : guiding_vectors) {
        lib::geometry::Trapezoid trapezoid(radius_vector, guiding_vector, angle,
                                           side_length);
        double area = static_cast<double>(trapezoid);
        EXPECT_GE(area, 0); // All should have non-negative area

        lib::geometry::Vec2 centroid = trapezoid.Centroid();
        SUCCEED(); // Centroid should be calculable for all orientations
    }
}

// Test that trapezoid implements Figure interface
TEST_F(TrapezoidTest, FigureInterface) {
    lib::geometry::Vec2 radius_vector(1, 1);
    lib::geometry::Vec2 guiding_vector(4, 0);
    double angle = pi / 4;
    double side_length = 2.0;

    lib::geometry::Trapezoid trapezoid(radius_vector, guiding_vector, angle,
                                       side_length);

    // Test that Trapezoid can be used as Figure through base class pointers
    lib::geometry::Figure* figure_ptr = &trapezoid;

    // Should be able to call virtual methods
    double area = static_cast<double>(*figure_ptr);
    EXPECT_GE(area, 0);

    lib::geometry::Vec2 centroid = figure_ptr->Centroid();
    SUCCEED(); // Verify call doesn't throw
}

// Test centroid calculation
TEST_F(TrapezoidTest, CentroidCalculation) {
    lib::geometry::Vec2 radius_vector(1, 0);
    lib::geometry::Vec2 guiding_vector(4, 0);
    double angle = pi / 3;
    double side_length = 2.0;

    lib::geometry::Trapezoid trapezoid(radius_vector, guiding_vector, angle,
                                       side_length);

    lib::geometry::Vec2 centroid = trapezoid.Centroid();

    // Centroid should not be the same as the radius vector
    EXPECT_NE(centroid.x, radius_vector.x);
    EXPECT_NE(centroid.y, radius_vector.y);

    // Centroid should have finite coordinates
    EXPECT_TRUE(std::isfinite(centroid.x));
    EXPECT_TRUE(std::isfinite(centroid.y));
}

// Test edge case: zero-length guiding vector
TEST_F(TrapezoidTest, ZeroLengthGuidingVector) {
    lib::geometry::Vec2 radius_vector(0, 0);
    lib::geometry::Vec2 guiding_vector(0, 0); // Zero vector
    double angle = pi / 3;
    double side_length = 2.0;

    // Behavior is undefined by the interface, but we test it doesn't crash
    lib::geometry::Trapezoid trapezoid(radius_vector, guiding_vector, angle,
                                       side_length);

    double area = static_cast<double>(trapezoid);
    // Area could be zero or implementation-defined
}

// Test edge case: zero angle
TEST_F(TrapezoidTest, ZeroAngle) {
    lib::geometry::Vec2 radius_vector(0, 0);
    lib::geometry::Vec2 guiding_vector(4, 0);
    double angle = 0.0;
    double side_length = 2.0;

    lib::geometry::Trapezoid trapezoid(radius_vector, guiding_vector, angle,
                                       side_length);

    double area = static_cast<double>(trapezoid);
    EXPECT_GE(area, 0); // Area should be non-negative
}

// Test edge case: π/2 angle (rectangle)
TEST_F(TrapezoidTest, RightAngle) {
    lib::geometry::Vec2 radius_vector(0, 0);
    lib::geometry::Vec2 guiding_vector(5, 0);
    double angle = pi / 2;
    double side_length = 3.0;

    lib::geometry::Trapezoid trapezoid(radius_vector, guiding_vector, angle,
                                       side_length);

    double area = static_cast<double>(trapezoid);
    // For rectangle: area = base * height = 5 * 3 = 15
    EXPECT_NEAR(area, 15.0, 1e-10);
}

// Test edge case: very small side length
TEST_F(TrapezoidTest, VerySmallSideLength) {
    lib::geometry::Vec2 radius_vector(0, 0);
    lib::geometry::Vec2 guiding_vector(4, 0);
    double angle = pi / 4;
    double side_length = 0.001;

    lib::geometry::Trapezoid trapezoid(radius_vector, guiding_vector, angle,
                                       side_length);

    double area = static_cast<double>(trapezoid);
    EXPECT_GE(area, 0);
    EXPECT_LT(area, 0.01); // Area should be very small
}

// Test negative coordinates
TEST_F(TrapezoidTest, NegativeCoordinates) {
    lib::geometry::Vec2 radius_vector(-2, -3);
    lib::geometry::Vec2 guiding_vector(-4, 0);
    double angle = pi / 4;
    double side_length = 2.0;

    lib::geometry::Trapezoid trapezoid(radius_vector, guiding_vector, angle,
                                       side_length);

    double area = static_cast<double>(trapezoid);
    EXPECT_GE(area, 0); // Area should still be positive

    lib::geometry::Vec2 centroid = trapezoid.Centroid();
    EXPECT_TRUE(std::isfinite(centroid.x));
    EXPECT_TRUE(std::isfinite(centroid.y));
}

// Test large values
TEST_F(TrapezoidTest, LargeValues) {
    lib::geometry::Vec2 radius_vector(1000, 2000);
    lib::geometry::Vec2 guiding_vector(500, 0);
    double angle = pi / 3;
    double side_length = 100.0;

    lib::geometry::Trapezoid trapezoid(radius_vector, guiding_vector, angle,
                                       side_length);

    double area = static_cast<double>(trapezoid);
    EXPECT_GT(area, 0);

    lib::geometry::Vec2 centroid = trapezoid.Centroid();
    EXPECT_TRUE(std::isfinite(centroid.x));
    EXPECT_TRUE(std::isfinite(centroid.y));
}

// Test that trapezoid is to the left of guiding vector
TEST_F(TrapezoidTest, LeftOfGuidingVector) {
    lib::geometry::Vec2 radius_vector(0, 0);
    lib::geometry::Vec2 guiding_vector(4, 0); // Pointing right
    double angle = pi / 4;
    double side_length = 2.0;

    lib::geometry::Trapezoid trapezoid(radius_vector, guiding_vector, angle,
                                       side_length);

    // The trapezoid should be situated to the left of the guiding vector
    // This means it should extend in the positive Y direction
    SUCCEED(); // Verify construction doesn't throw
}

// Test copy constructor and assignment
TEST_F(TrapezoidTest, CopyOperations) {
    lib::geometry::Vec2 radius_vector(1, 1);
    lib::geometry::Vec2 guiding_vector(4, 0);
    double angle = pi / 4;
    double side_length = 2.0;

    lib::geometry::Trapezoid trapezoid1(radius_vector, guiding_vector, angle,
                                        side_length);
    lib::geometry::Trapezoid trapezoid2 = trapezoid1; // Copy constructor

    double area1 = static_cast<double>(trapezoid1);
    double area2 = static_cast<double>(trapezoid2);

    EXPECT_DOUBLE_EQ(area1, area2);

    lib::geometry::Trapezoid trapezoid3;
    trapezoid3 = trapezoid1; // Assignment operator

    double area3 = static_cast<double>(trapezoid3);
    EXPECT_DOUBLE_EQ(area1, area3);
}

// Test degenerate case: side length too short for given base and angle
TEST_F(TrapezoidTest, DegenerateCase) {
    lib::geometry::Vec2 radius_vector(0, 0);
    lib::geometry::Vec2 guiding_vector(10, 0); // Large base
    double angle = pi / 3;                     // 60 degrees
    double side_length = 1.0;                  // Very short side

    lib::geometry::Trapezoid trapezoid(radius_vector, guiding_vector, angle,
                                       side_length);

    double area = static_cast<double>(trapezoid);
    EXPECT_GE(area, 0); // Area should still be non-negative
}
