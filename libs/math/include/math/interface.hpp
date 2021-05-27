//
// Модуль Ветошкина Артёма
//

#pragma once

#include <utility>

#include <math/utilits.hpp>


namespace math {

using runge_func = std::function<void(const math::coords_t &
                                      , math::coords_t &, math::decimal_t)>;

using visit_runge_func = std::function<void(const math::coords_t &
                                            , math::decimal_t)>;

class IRungeKuttaMethod {
  public:
    IRungeKuttaMethod() = delete;

    IRungeKuttaMethod(runge_func func, math::coords_t start_x)
            : _func(std::move(func))
              , _start_x(start_x) {}

    virtual math::decimal_t do_step(math::decimal_t t, math::decimal_t dt) = 0;

    virtual void do_duration_step(math::decimal_t start_t
                                  , math::decimal_t end_t
                                  , math::decimal_t dt
                                  , visit_runge_func visitor) = 0;

    virtual void update_start_x(math::coords_t start_x) {
        _start_x = start_x;
    }

    [[nodiscard]]
    virtual math::coords_t get_start_x() const {
        return _start_x;
    }

    virtual ~IRungeKuttaMethod() = default;

  protected:
    runge_func _func;
    math::coords_t _start_x;
};

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
