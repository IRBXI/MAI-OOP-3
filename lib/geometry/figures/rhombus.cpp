#include "rhombus.hpp"
#include <cmath>

namespace lib::geometry {

Rhombus::Rhombus() noexcept {
    for (std::size_t i = 0; i < 4; ++i) {
        points_[i] = {0.0, 0.0};
    }
};

Rhombus::Rhombus(const Vec2& radius_vector, const Vec2& guiding_vector,
                 double angle_radians) noexcept {
    const double rotation_angles[2] = {M_PI - angle_radians, angle_radians};
    side_ = guiding_vector.Length();
    angle_radians_ = angle_radians;
    Vec2 cur_point = radius_vector;
    Vec2 guide = guiding_vector;
    for (std::size_t i = 0; i < 4; ++i) {
        points_[i] = cur_point;
        cur_point += guide;
        guide = Vec2::Rotate(guide, rotation_angles[i % 2]);
    }
}

Rhombus::operator double() const noexcept {
    return side_ * side_ * std::sin(angle_radians_);
}

Vec2 Rhombus::Centroid() const noexcept {
    return Vec2::GetCentroid(4, points_);
}

std::ostream& operator<<(std::ostream& os, const Rhombus& rhombus) {
    os << "Rhombus:\n";
    for (std::size_t i = 0; i < 4; ++i) {
        os << rhombus.points_[i];
    }
    os << std::endl;
    return os;
}

std::istream& operator>>(std::istream& is, Rhombus& rhombus) {
    Vec2 radius_vector, guiding_vector;
    double angle_radians;
    is >> radius_vector >> guiding_vector >> angle_radians;

    rhombus = Rhombus(radius_vector, guiding_vector, angle_radians);

    return is;
}

} // namespace lib::geometry
