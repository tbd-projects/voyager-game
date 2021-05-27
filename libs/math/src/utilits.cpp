#define _USE_MATH_DEFINES

#include <cmath>
#include <functional>



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

coords_t::operator std::pair<decimal_t, decimal_t>() const {
    return std::pair<decimal_t, decimal_t>(x, y);
}

coords_t coords_t::operator*(coords_t coords) const {
    return coords_t(x * coords.x, y * coords.y);
}


//  ---------------------------GeometryFunction---------------------------------


coords_t GeometryFunction::rotate_point(coords_t point, decimal_t angle
                                        , coords_t basis) {
    point -= basis;
    decimal_t rad_angle = Utilits::to_rad(angle);
    decimal_t cos_angle = std::cos(rad_angle);
    decimal_t sin_angle = std::sin(rad_angle);

    decimal_t new_x = point.x * cos_angle - point.y * sin_angle;
    decimal_t new_y = point.x * sin_angle + point.y * cos_angle;
    return coords_t(new_x, new_y) + basis;
}

GeometryFunction::point_relative GeometryFunction::point_relative_line(
        Vector2d line
        , coords_t start_line
        , coords_t point) {
    Vector2d vector_to_point(point - start_line);
    decimal_t skew_product =
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


bool Utilits::is_null(decimal_t value) {
    return std::abs(value) < decimal_epsilon;
}

decimal_t Utilits::to_grad(decimal_t angle) {
    return angle * dec(180.0) / (decimal_t) M_PI;
}

decimal_t Utilits::to_rad(decimal_t angle) {
    return angle * (decimal_t) M_PI / dec(180.0);
}

bool Utilits::is_equal(decimal_t value_1, decimal_t value_2) {
    return is_null(value_1 - value_2);
}

decimal_t Utilits::decimal_epsilon = dec(1e-5);


//  ---------------------------AlgebraicMethods---------------------------------


decimal_t AlgebraicMethods::solve_equastion_by_Halley(
        const std::function<return_for_solve_equastion(decimal_t)> &func
        , decimal_t start_x_value, size_t number_iteration) {
    for (size_t i = 0; i < number_iteration; ++i) {
        math::decimal_t last_x = start_x_value;
        return_for_solve_equastion returns = func(start_x_value);
        math::decimal_t first_devide =
                returns.res_base_func / returns.res_first_deriv_func;
        math::decimal_t second_devide =
                returns.res_second_deriv_func / (dec(2) *
                returns.res_first_deriv_func);

        start_x_value =
                last_x - first_devide / (1 - first_devide * second_devide);
    }
    return start_x_value;
}

}  // namespace math
