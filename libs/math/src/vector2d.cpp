#include <cmath>
#include "debug/exception.hpp"
#include "vector2d.hpp"
#include "utilits.hpp"

namespace math {


//  -------------------------------Vector2d------------------------------------


Vector2d::Vector2d(coords_t coords)
        : _coords(coords) {}

Vector2d::Vector2d(coords_t first_point, coords_t second_point)
        : _coords(second_point - first_point) {}

Vector2d::Vector2d(decimal_t angle, decimal_t len)
        : _coords() {
    math::GeometryFunction geometry;
    _coords = geometry.rotate_point(coords_t(0, len), angle, coords_t(0, 0));
}

coords_t Vector2d::get_coords() const {
    return _coords;
}

decimal_t Vector2d::len() const {
    return std::sqrt(sqr_len());
}

decimal_t Vector2d::sqr_len() const {
    return _coords.x * _coords.x + _coords.y * _coords.y;
}

bool Vector2d::is_zero() const {
    return Utilits::is_null(sqr_len());
}

Vector2d Vector2d::normalize() const {
    math::decimal_t vec_len = len();
    return Vector2d(coords_t(_coords.x / vec_len, _coords.y / vec_len));
}

bool Vector2d::is_normal() const {
    return Utilits::is_equal(sqr_len(), 1);
}

decimal_t Vector2d::operator^(const Vector2d& vector) const {
    return (*this * vector) / (len() * vector.len());
}

decimal_t Vector2d::operator*(const Vector2d& vector) const {
    return _coords.x * vector._coords.x + _coords.y * vector._coords.y;
}

Vector2d Vector2d::operator*(decimal_t k) const {
    return Vector2d(coords_t(_coords.x * k, _coords.y * k));
}

Vector2d operator*(decimal_t k, const Vector2d& vector) {
    return Vector2d(coords_t(vector._coords.x * k, vector._coords.y * k));
}

Vector2d Vector2d::operator+(const Vector2d &vector) const {
    return Vector2d(_coords + vector._coords);
}

Vector2d &Vector2d::operator+=(const Vector2d &vector) {
    *this = *this + vector;
    return *this;
}

bool Vector2d::operator==(const Vector2d &vector) const {
    return _coords == vector._coords;
}

Vector2d Vector2d::operator/(decimal_t k) const {
    if (Utilits::is_null(k)) {
        throw debug::ARG_ARGUMENT_ERROR("detected try to div on zero");
    }
    return Vector2d(coords_t(_coords.x / k, _coords.y / k));
}

}  // namespace math
