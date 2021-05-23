#pragma once

#define _USE_MATH_DEFINES

#include <functional>
#include <utility>
#include <cmath>

namespace math {

typedef double decimal_t;

#define d(var) decimal_t(var)

class Vector2d;

struct coords_t {
    decimal_t x;
    decimal_t y;

    coords_t();

    coords_t(decimal_t x, decimal_t y);

    bool operator==(coords_t coords_t) const;

    operator std::pair<decimal_t, decimal_t>() const;

    coords_t operator-(coords_t coords) const;

    coords_t operator+(coords_t coords) const;

    coords_t &operator-=(coords_t coords);

    coords_t &operator+=(coords_t coords);

    coords_t operator*(coords_t coords) const;

    coords_t operator-(decimal_t offset) const;

    coords_t operator+(decimal_t offset) const;

    coords_t &operator-=(decimal_t offset);

    coords_t &operator+=(decimal_t offset);
};

const math::decimal_t const_2_pi = d(2) * (decimal_t)M_PI;

class Utilits {
  public:
    static bool is_null(math::decimal_t value);

    static bool is_equal(math::decimal_t value_1, math::decimal_t value_2);

    static math::decimal_t to_rad(math::decimal_t angle);

    static math::decimal_t to_grad(math::decimal_t angle);

    static math::decimal_t decimal_epsilon;
};

class AlgebraicMethods {
  public:
    struct return_for_solve_equastion {
        decimal_t res_base_func;
        decimal_t res_first_deriv_func;
        decimal_t res_second_deriv_func;
    };

    decimal_t solve_equastion_by_Halley(
            const std::function<return_for_solve_equastion(decimal_t x)>& func
            , decimal_t start_x_value, size_t number_iteration);
};

class GeometryFunction {
  public:
    enum class point_relative {
        at_left,
        at_right,
        on_line
    };

    coords_t rotate_point(coords_t point, decimal_t angle, coords_t basis);

    point_relative point_relative_line(Vector2d line, coords_t start_line
                                       , coords_t point);
};

}  // namespace math
