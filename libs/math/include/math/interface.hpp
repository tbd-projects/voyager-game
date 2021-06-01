#pragma once

#include <utility>

#include <math/utilits.hpp>


namespace math {

struct system_of_diff_equations {
    math::decimal_t result_first_equation;
    math::decimal_t result_second_equation;

    system_of_diff_equations(math::decimal_t v_result_first_equation = 0.,
                             math::decimal_t v_result_second_equation = 0.)
            : result_first_equation(v_result_first_equation)
              , result_second_equation(v_result_second_equation) {}
};

using runge_func = std::function<void(const system_of_diff_equations &,
                                      system_of_diff_equations &,
                                      math::decimal_t)>;

using visit_runge_func = std::function<void(const system_of_diff_equations &,
                                            math::decimal_t)>;


class IRungeKuttaMethod {
  public:
    IRungeKuttaMethod() = delete;

    IRungeKuttaMethod(runge_func func, system_of_diff_equations start_value)
            : _func(std::move(func))
              , _system_equations(start_value) {}

    virtual math::decimal_t do_step(math::decimal_t t, math::decimal_t dt) = 0;

    virtual void
    do_duration_step(math::decimal_t start_t, math::decimal_t end_t,
                     math::decimal_t dt, visit_runge_func visitor) = 0;

    virtual void update_start_x(system_of_diff_equations start_value) {
        _system_equations = start_value;
    }

    [[nodiscard]]
    virtual system_of_diff_equations get_result_equations() const {
        return _system_equations;
    }

    virtual ~IRungeKuttaMethod() = default;

  protected:
    runge_func _func;
    system_of_diff_equations _system_equations;
};

class IScalable {
  public:
    virtual void scale(math::decimal_t scale) = 0;

    virtual ~IScalable() = default;
};

class IIntresectable {
  public:
    [[nodiscard]]
    virtual bool intersects(const IIntresectable &object) const = 0;

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

    virtual void rotate(math::decimal_t offset_angle) = 0;

    virtual ~IRotatable() = default;
};

}  // namespace math
