#pragma once

#include <math/utilits.hpp>

namespace math {

class Vector2d {
  public:
    Vector2d() = default;

    explicit Vector2d(coords_t coords);

    Vector2d(coords_t first_point, coords_t second_point);

    Vector2d(decimal_t angle, decimal_t len);

    coords_t get_coords() const;

    decimal_t len() const;

    decimal_t sqr_len() const;

    bool is_zero() const;

    Vector2d normalize() const;

    bool is_normal() const;

    decimal_t operator^(Vector2d vector) const;

    decimal_t operator*(Vector2d vector) const;

    Vector2d operator*(decimal_t k) const;

    friend Vector2d operator*(decimal_t k, Vector2d vector);

  private:
    coords_t _coords;
};

}  // namespace math
