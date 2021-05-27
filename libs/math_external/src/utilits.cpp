#include <debug/exception.hpp>

#include "math_external/utilits.hpp"

namespace math::external {

RungeKuttaBoostMethod::RungeKuttaBoostMethod(runge_func func
                                             , math::coords_t start_x)
        : IRungeKuttaMethod(std::move(func), start_x)
          , _stepper() {}

math::decimal_t RungeKuttaBoostMethod::do_step(math::decimal_t t
                                               , math::decimal_t dt) {
    if (dt < 0) {
        throw debug::ARG_ARGUMENT_ERROR("Got negative dt in loop "
                                        "duration_step of Runge Kutta method, "
                                        "that's value is impossible "
                                        + std::to_string(dt));
    }

    auto func = [this](const state_type& x, state_type& dx, double t) -> void {
        math::coords_t v_x = {x[0], x[1]};
        math::coords_t v_dx = {dx[0], dx[1]};

        _func(v_x, v_dx, t);

        dx[0] = v_dx.x;
        dx[1] = v_dx.y;
    };

    state_type x = {_start_x.x, _start_x.y};
    _stepper.do_step(func, x, t, dt);

    _start_x.x = x[0];
    _start_x.y = x[1];

    return  _start_x.x;
}

void RungeKuttaBoostMethod::do_duration_step(math::decimal_t start_t
                                             , math::decimal_t end_t
                                             , math::decimal_t dt
                                             , visit_runge_func visitor) {
    if (math::Utilits::is_null(dt) || dt < 0) {
        throw debug::ARG_ARGUMENT_ERROR("Got zero or negative dt in loop "
                                        "duration_step of Runge Kutta method, "
                                        "that's value is impossible "
                                        + std::to_string(dt));
    }

    if (start_t > end_t) {
        throw debug::ARG_ARGUMENT_ERROR("Start t is the greatest then end_t "
                                        "that's values is impossible "
                                        + std::to_string(start_t)
                                        + std::to_string(end_t));
    }

    auto func = [this](const state_type& x, state_type& dx, double t) -> void {
        math::coords_t v_x = {x[0], x[1]};
        math::coords_t v_dx = {dx[0], dx[1]};

        _func(v_x, v_dx, t);

        dx[0] = v_dx.x;
        dx[1] = v_dx.y;
    };

    auto visit = [visitor](const state_type& x, double t) -> void {
        math::coords_t v_x = {x[0], x[1]};

        visitor(v_x, t);
    };

    state_type x = {_start_x.x, _start_x.y};
    boost::numeric::odeint::integrate_const(_stepper, func, x
                                            , start_t, end_t, dt , visit);

    _start_x.x = x[0];
    _start_x.y = x[1];
}

const math::decimal_t RungeKuttaBoostMethod::method_epsilon = 1e-3;

}  // namespace math::external
