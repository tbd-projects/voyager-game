#pragma once


namespace math {

typedef float decimal_t;

class Vector2d;

struct coords_t {
    decimal_t x;
    decimal_t y;

    coords_t();

    coords_t(decimal_t x, decimal_t y);

    bool operator==(coords_t coords_t) const;

    coords_t operator-(coords_t coords) const;

    coords_t operator+(coords_t coords) const;

    coords_t& operator-=(coords_t coords);

    coords_t& operator+=(coords_t coords);

    coords_t operator-(decimal_t offset) const;

    coords_t operator+(decimal_t offset) const;

    coords_t& operator-=(decimal_t offset);

    coords_t& operator+=(decimal_t offset);
};

class Utilits {
  public:
    static bool is_null(math::decimal_t value);

    static bool is_equal(math::decimal_t value_1, math::decimal_t value_2);

    static math::decimal_t to_rad(math::decimal_t angle);

    static math::decimal_t to_grad(math::decimal_t angle);

    static math::decimal_t decimal_epsilon;
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
