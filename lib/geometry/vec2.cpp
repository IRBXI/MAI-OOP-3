#include "vec2.hpp"

#include <cmath>

namespace lib::geometry {

double Vec2::Length() const noexcept { return sqrt(pow(x, 2) + pow(y, 2)); }

void Vec2::Normalize() noexcept {
    double len = Length();
    x /= len;
    y /= len;
}

Vec2 Vec2::Rotate(const Vec2& v, double angle_radians) noexcept {
    double new_x = v.x * cos(angle_radians) - v.y * sin(angle_radians);
    double new_y = v.x * sin(angle_radians) + v.y * cos(angle_radians);
    return {new_x, new_y};
}

Vec2 Vec2::GetCentroid(std::size_t n, const Vec2* arr) noexcept {
    Vec2 sum;
    for (std::size_t i = 0; i < n; ++i) {
        sum += arr[i];
    }
    return sum / static_cast<double>(n);
}

Vec2& Vec2::operator+=(const Vec2& rhs) noexcept {
    this->x += rhs.x;
    this->y += rhs.y;
    return *this;
}

Vec2 Vec2::operator+(const Vec2& rhs) noexcept {
    Vec2 res = *this;
    res += rhs;
    return res;
}

Vec2& Vec2::operator-=(const Vec2& rhs) noexcept {
    this->x -= rhs.x;
    this->y -= rhs.y;
    return *this;
}

Vec2 Vec2::operator-(const Vec2& rhs) noexcept {
    Vec2 res = *this;
    res -= rhs;
    return res;
}

Vec2& Vec2::operator*=(const double v) noexcept {
    this->x *= v;
    this->y *= v;
    return *this;
}

Vec2 Vec2::operator*(const double v) noexcept {
    Vec2 res = *this;
    res *= v;
    return res;
}

Vec2& Vec2::operator/=(const double v) noexcept {
    this->x /= v;
    this->y /= v;
    return *this;
}

Vec2 Vec2::operator/(const double v) noexcept {
    Vec2 res = *this;
    res /= v;
    return res;
}

bool Vec2::operator==(const Vec2& rhs) noexcept {
    return std::abs(x - rhs.x) < EPS and std::abs(y - rhs.y) < EPS;
}

std::ostream& operator<<(std::ostream& os, const Vec2& vec) {
    os << '(' << vec.x << ", " << vec.y << ')' << std::endl;
    return os;
}

std::istream& operator>>(std::istream& is, Vec2& vec) {
    is >> vec.x >> vec.y;
    return is;
}

} // namespace lib::geometry
