#pragma once

#include <math/utilits.hpp>

namespace math {

class Vector2d {
  public:
    Vector2d() = default;

    explicit Vector2d(coords_t coords);

    explicit Vector2d(coords_t first_point, coords_t second_point);

    explicit Vector2d(decimal_t angle, decimal_t len);

    [[nodiscard]]
    coords_t get_coords() const;

    [[nodiscard]]
    decimal_t len() const;

    [[nodiscard]]
    decimal_t sqr_len() const;

    [[nodiscard]]
    bool is_zero() const;

    [[nodiscard]]
    Vector2d normalize() const;

    [[nodiscard]]
    bool is_normal() const;

    bool operator==(const Vector2d& vector) const;

    Vector2d operator+(const Vector2d& vector) const;

    Vector2d& operator+=(const Vector2d& vector);

    decimal_t operator^(const Vector2d& vector) const;

    decimal_t operator*(const Vector2d& vector) const;

    Vector2d operator*(decimal_t k) const;

    Vector2d operator/(decimal_t k) const;

    friend Vector2d operator*(decimal_t k, const Vector2d& vector);

  private:
    coords_t _coords;
};

}  // namespace math
