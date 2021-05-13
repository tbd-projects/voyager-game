#pragma once

#include <math/utilits.hpp>

namespace math {

class IScalable {
  public:
    virtual void scale(math::decimal_t scale) = 0;

    virtual ~IScalable() = default;
};

class IIntresectable {
  public:
    [[nodiscard]]
    virtual bool intresect(const IIntresectable &object) const = 0;

    [[nodiscard]]
    virtual bool is_point_in_polygon(math::coords_t point) const = 0;

    virtual ~IIntresectable() = default;
};

class IPositionable {
  public:
    [[nodiscard]]
    virtual math::coords_t get_pos() const noexcept = 0;

    virtual void set_pos(math::coords_t pos) = 0;

    virtual ~IPositionable() = default;
};

class IRotatable {
  public:
    [[nodiscard]]
    virtual math::decimal_t get_rotation() const noexcept = 0;

    virtual void set_rotation(math::decimal_t angle) = 0;

    virtual void add_rotation(math::decimal_t offset_angle) = 0;

    virtual ~IRotatable() = default;
};

}  // namespace math
