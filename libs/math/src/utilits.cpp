#define _USE_MATH_DEFINES

#include <cmath>

#include "utilits.hpp"
#include "vector2d.hpp"

namespace math {


//  ---------------------------------coords_t----------------------------------


coords_t::coords_t()
        : x(0)
          , y(0) {}

coords_t::coords_t(decimal_t v_x, decimal_t v_y)
        : x(v_x)
          , y(v_y) {}

bool coords_t::operator==(coords_t coords) const {
    return Utilits::is_equal(coords.x, x) && Utilits::is_equal(coords.y, y);
}

coords_t coords_t::operator-(coords_t coords) const {
    return coords_t(x - coords.x, y - coords.y);
}

coords_t coords_t::operator+(coords_t coords) const {
    return coords_t(x + coords.x, y + coords.y);
}

coords_t &coords_t::operator-=(coords_t coords) {
    *this = *this - coords;
    return *this;
}

coords_t &coords_t::operator+=(coords_t coords) {
    *this = *this + coords;
    return *this;
}

coords_t coords_t::operator-(decimal_t offset) const {
    return coords_t(x - offset, y - offset);
}

coords_t coords_t::operator+(decimal_t offset) const {
    return coords_t(x + offset, y + offset);
}

coords_t &coords_t::operator-=(decimal_t offset) {
    *this = *this - offset;
    return *this;
}

coords_t &coords_t::operator+=(decimal_t offset) {
    *this = *this + offset;
    return *this;
}


//  ---------------------------GeometryFunction---------------------------------


coords_t GeometryFunction::rotate_point(coords_t point, decimal_t angle
                                        , coords_t basis) {
    point -= basis;
    math::decimal_t rad_angle = Utilits::to_rad(angle);
    math::decimal_t cos_angle = std::cos(rad_angle);
    math::decimal_t sin_angle = std::sin(rad_angle);

    math::decimal_t new_x = point.x * cos_angle - point.y * sin_angle;
    math::decimal_t new_y = point.x * sin_angle + point.y * cos_angle;
    return coords_t(new_x, new_y) + basis;
}

GeometryFunction::point_relative GeometryFunction::point_relative_line(
                                                        Vector2d line
                                                        , coords_t start_line
                                                        , coords_t point) {
    math::Vector2d vector_to_point(point - start_line);
    math::decimal_t skew_product =
            line.get_coords().x * vector_to_point.get_coords().y -
            vector_to_point.get_coords().x * line.get_coords().y;

    if (skew_product > 0) {
        return point_relative::at_left;
    }
    if (skew_product < 0) {
        return point_relative::at_right;
    }
    return point_relative::on_line;
}


//  -------------------------------Utilits--------------------------------------


bool Utilits::is_null(math::decimal_t value) {
    return std::abs(value) < decimal_epsilon;
}

math::decimal_t Utilits::to_grad(math::decimal_t angle) {
    return angle * (math::decimal_t) 180.0 / (math::decimal_t) M_PI;
}

math::decimal_t Utilits::to_rad(math::decimal_t angle) {
    return angle * (math::decimal_t) M_PI / (math::decimal_t) 180.0;
}

bool Utilits::is_equal(math::decimal_t value_1, math::decimal_t value_2) {
    return is_null(value_1 - value_2);
}

math::decimal_t Utilits::decimal_epsilon = 1e-5;

}  // namespace math
