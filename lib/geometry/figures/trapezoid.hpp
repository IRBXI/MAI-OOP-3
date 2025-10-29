#pragma once

#include "figure.hpp"

namespace lib::geometry {

// Isosceles trapezoid (равнобедренная трапеция)
class Trapezoid : public Figure {
  private:
    Vec2 points_[4];
    double greater_base_;
    double lesser_base_;
    double side_;

  public:
    Trapezoid() noexcept;

    // The radius vector indicates the position of the trapezoid on the plane
    // The radius vector is one of the points of the trapezoid
    // The guiding vector should be colinear with the greater base of the
    // trapezoid
    // The trapezoid will be situated to the left of the guiding vector
    // The length of the greater base will be equal to the length of the guiding
    // vector
    // The angle in radians is the angle between the greater base and the side
    Trapezoid(const Vec2& radius_vector, const Vec2& guiding_vector,
              double angle_radians, double side_length) noexcept;

    explicit operator double() const noexcept final;
    Vec2 Centroid() const noexcept final;

    // Reading Trapezoid from a stream uses the same structure as a constructor
    // with radius vector, a guiding vector, an angle in radians and the side
    // length Essentially it just reads two vectors, an angle and the side
    // length from the stream and when calls the constructor
    friend std::istream& operator>>(std::istream& is, Trapezoid& trapezoid);
    friend std::ostream& operator<<(std::ostream& os,
                                    const Trapezoid& trapezoid);
};

} // namespace lib::geometry
