#pragma once

#include "figure.hpp"
#include "vec2.hpp"

namespace lib::geometry {

class Pentagon : public Figure {
  private:
    Vec2 points_[5];
    double side_;

  public:
    Pentagon() noexcept;

    // The radius vector indicates the position of the pentagon on the plane
    // The radius vector is one of the points of the pentagon
    // The guiding vector should be colinear with one of the sides of the
    // pentagon
    // The pentagon will be situated to the left of the guiding vector
    // The length of the side will be equal to the length of the guiding vector
    Pentagon(const Vec2& radius_vector, const Vec2& guiding_vector) noexcept;

    explicit operator double() const noexcept final;
    Vec2 Centroid() const noexcept final;

    // Reading Pentagon from a stream uses the same structure as a constructor
    // with radius vector and a guiding vector
    // Essentially it just reads two vectors from the stream and when calls the
    // constructor
    friend std::istream& operator>>(std::istream& is, Pentagon& pent);
    friend std::ostream& operator<<(std::ostream& os, const Pentagon& pent);
};

} // namespace lib::geometry
