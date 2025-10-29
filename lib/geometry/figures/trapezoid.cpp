#include "trapezoid.hpp"

#include <cmath>

namespace lib::geometry {

Trapezoid::Trapezoid() noexcept {
    for (std::size_t i = 0; i < 4; ++i) {
        points_[i] = {0.0, 0.0};
    }
}

Trapezoid::Trapezoid(const Vec2& radius_vector, const Vec2& guiding_vector,
                     double angle_radians, double side_length) noexcept {
    const double rotation_angles[2] = {M_PI - angle_radians, angle_radians};
    greater_base_ = guiding_vector.Length();
    side_ = side_length;
    lesser_base_ = greater_base_ - 2.0 * (side_ * std::cos(angle_radians));

    Vec2 cur_point = radius_vector;
    points_[0] = cur_point;

    cur_point += guiding_vector;
    points_[1] = cur_point;

    Vec2 guide = Vec2::Rotate(guiding_vector, rotation_angles[0]);
    guide.Normalize();
    guide *= side_length;
    cur_point += guide;
    points_[2] = cur_point;

    guide = Vec2::Rotate(guide, rotation_angles[1]);
    guide.Normalize();
    guide *= lesser_base_;
    cur_point += guide;
    points_[3] = cur_point;
}

Trapezoid::operator double() const noexcept {
    return ((greater_base_ + lesser_base_) / 4.0) *
           std::sqrt((greater_base_ - lesser_base_ + 2 * side_) *
                     (lesser_base_ - greater_base_ + 2 * side_));
}

Vec2 Trapezoid::Centroid() const noexcept {
    return Vec2::GetCentroid(4, points_);
}

std::istream& operator>>(std::istream& is, Trapezoid& trapezoid) {
    Vec2 radius_vector, guiding_vector;
    double angle_radians;
    double side_length;
    is >> radius_vector >> guiding_vector >> angle_radians >> side_length;

    trapezoid =
        Trapezoid(radius_vector, guiding_vector, angle_radians, side_length);

    return is;
}

std::ostream& operator<<(std::ostream& os, const Trapezoid& trapezoid) {
    os << "Trapezoid:\n";
    for (std::size_t i = 0; i < 4; ++i) {
        os << trapezoid.points_[i];
    }
    os << std::endl;
    return os;
}

} // namespace lib::geometry
