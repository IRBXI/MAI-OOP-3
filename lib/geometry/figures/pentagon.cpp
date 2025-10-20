#include "pentagon.hpp"
#include <math.h>

namespace {
constexpr double ROTATION_ANGLE = M_PI - ((5 - 2) * M_PI) / 5;
}

namespace lib::geometry {

Pentagon::Pentagon() noexcept {
    side_ = 0.0;
    for (std::size_t i = 0; i < 5; ++i) {
        points_[i] = {0.0, 0.0};
    }
}

Pentagon::Pentagon(const Vec2& radius_vector,
                   const Vec2& guiding_vector) noexcept {
    side_ = guiding_vector.Length();
    Vec2 cur_point = radius_vector;
    Vec2 guide = guiding_vector;
    for (std::size_t i = 0; i < 5; ++i) {
        points_[i] = cur_point;
        cur_point += guide;
        guide = Vec2::Rotate(guide, ROTATION_ANGLE);
    }
}

Pentagon::operator double() const noexcept {
    double area = 5.0 * side_ * side_ * std::tan(3.0 * M_PI / 10.0) / 4.0;
    return area;
}

Vec2 Pentagon::Centroid() const noexcept {
    return Vec2::GetCentroid(5, points_);
}

std::ostream& operator<<(std::ostream& os, const Pentagon& pentagon) {
    os << "Pentagon:\n";
    for (std::size_t i = 0; i < 5; ++i) {
        os << pentagon.points_[i];
    }
    os << std::endl;
    return os;
}

std::istream& operator>>(std::istream& is, Pentagon& pentagon) {
    Vec2 radius_vector, guiding_vector;
    is >> radius_vector >> guiding_vector;

    pentagon = Pentagon(radius_vector, guiding_vector);

    return is;
}

} // namespace lib::geometry
