

#include "utilits.hpp"

namespace math::external {

RungeKuttaBoostMethod::RungeKuttaBoostMethod(runge_func func
                                             , math::coords_t start_x)
        : IRungeKuttaMethod(std::move(func), start_x)
          , _stepper() {}

math::decimal_t RungeKuttaBoostMethod::do_step(math::decimal_t t
                                               , math::decimal_t dt) {
    auto func = [this](state_type& x, state_type& dx, double t) -> void {
        math::coords_t v_x = {x[0], x[1]};
        math::coords_t v_dx = {dx[0], dx[1]};

        _func(v_x, v_dx, t);

        x[0] = v_x.x;
        x[1] = v_x.y;
        dx[0] = v_dx.x;
        dx[1] = v_dx.y;
    };

    state_type x = {_start_x.x, _start_x.y};
    _stepper.do_step(func, x, (double)t, (double)dt);

    _start_x.x = x[0];
    _start_x.y = x[1];

    return  _start_x.x;
}

void RungeKuttaBoostMethod::do_duration_step(math::decimal_t start_t
                                             , math::decimal_t end_t
                                             , math::decimal_t dt
                                             , visit_runge_func visitor) {
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

}  // namespace math
