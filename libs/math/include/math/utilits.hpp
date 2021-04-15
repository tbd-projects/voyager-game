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
    coords_t rotate_point(coords_t point, decimal_t angle, coords_t basis);

    bool point_relative_line(Vector2d line, coords_t point);
};

}  // namespace math
