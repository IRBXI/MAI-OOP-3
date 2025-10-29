#pragma once

#include "figure.hpp"

namespace lib::geometry {

class Rhombus : public Figure {
  private:
    Vec2 points_[4];
    double side_;
    double angle_radians_;

  public:
    Rhombus() noexcept;

    // The radius vector indicates the position of the rhombus on the plane
    // The radius vector is one of the points of the rhombus
    // The guiding vector should be colinear with one of the sides of the
    // rhombus
    // The rhombus will be situated to the left of the guiding vector
    // The length of the side will be equal to the length of the guiding vector
    // The angle is the first angle while turning to the left
    Rhombus(const Vec2& radius_vector, const Vec2& guiding_vector,
            double angle_radians) noexcept;

    explicit operator double() const noexcept final;
    Vec2 Centroid() const noexcept final;

    // Reading Rhombus from a stream uses the same structure as a constructor
    // with radius vector, a guiding vector and an angle
    // Essentially it just reads two vectors and an angle from the stream and
    // when calls the constructor
    friend std::istream& operator>>(std::istream& is, Rhombus& rhombus);
    friend std::ostream& operator<<(std::ostream& os, const Rhombus& rhombus);
};

} // namespace lib::geometry
