#include "vector2d.h"


namespace math {


//-------------------------------Vector2d--------------------------------------


Vector2d::Vector2d(coords_t coords)
        : _coords(coords) {}

Vector2d::Vector2d(coords_t first_point, coords_t second_point)
        : _coords(second_point - first_point) {}

Vector2d::Vector2d(decimal_t angle, decimal_t len)
        : _coords() {}

coords_t Vector2d::get_coords() const {
    return coords_t();
}

decimal_t Vector2d::len() const {
    return 0;
}

decimal_t Vector2d::sqr_len() const {
    return 0;
}

bool Vector2d::is_zero() const {
    return false;
}

Vector2d Vector2d::normalize() const {
    return Vector2d();
}

bool Vector2d::is_normal() const {
    return false;
}

decimal_t Vector2d::operator^(Vector2d vector) const {
    return 0;
}

decimal_t Vector2d::operator*(Vector2d vector) const {
    return 0;
}

Vector2d Vector2d::operator*(decimal_t k) const {
    return Vector2d();
}

Vector2d operator*(decimal_t k, Vector2d vector) {
    return Vector2d();
}


}