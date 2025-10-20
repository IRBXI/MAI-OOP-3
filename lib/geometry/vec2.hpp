#pragma once

#include <istream>
#include <ostream>

namespace lib::geometry {

constexpr double EPS = 1e-6;

struct Vec2 {
    double x;
    double y;

    double Length() const noexcept;
    void Normalize() noexcept;

    static Vec2 Rotate(const Vec2& v, double angle_radians) noexcept;

    // Finds the centroid of the array of points
    // where n is the size of the array
    static Vec2 GetCentroid(std::size_t n, const Vec2* arr) noexcept;

    Vec2& operator+=(const Vec2& rhs) noexcept;
    Vec2 operator+(const Vec2& rhs) noexcept;
    Vec2& operator-=(const Vec2& rhs) noexcept;
    Vec2 operator-(const Vec2& rhs) noexcept;
    Vec2& operator*=(const double v) noexcept;
    Vec2 operator*(const double v) noexcept;
    Vec2& operator/=(const double v) noexcept;
    Vec2 operator/(const double v) noexcept;
    bool operator==(const Vec2& rhs) noexcept;

    friend std::ostream& operator<<(std::ostream& os, const Vec2& vec);
    friend std::istream& operator>>(std::istream& is, Vec2& vec);
};

} // namespace lib::geometry
