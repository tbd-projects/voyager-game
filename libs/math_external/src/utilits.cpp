#include <debug/exception.hpp>
#include <game_manager/config.hpp>

#include "math_external/utilits.hpp"


namespace math::external {

RungeKuttaBoostMethod::RungeKuttaBoostMethod(runge_func func,
                                 math::system_of_diff_equations start_value)
        : IRungeKuttaMethod(std::move(func), start_value)
          , _stepper() {}

math::decimal_t RungeKuttaBoostMethod::do_step(math::decimal_t t,
                                               math::decimal_t dt) {
    if (dt < 0) {
        throw debug::ARG_ARGUMENT_ERROR("Got negative dt in loop "
                                        "duration_step of Runge Kutta method, "
                                        "that's value is impossible "
                                        + std::to_string(dt));
    }

    auto func = [this](const state_type &x, state_type &dx, double t) -> void {
        math::system_of_diff_equations v_x = {x[0], x[1]};
        math::system_of_diff_equations v_dx = {dx[0], dx[1]};

        _func(v_x, v_dx, t);

        dx[0] = v_dx.result_first_equation;
        dx[1] = v_dx.result_second_equation;
    };

    state_type x = {_system_equations.result_first_equation,
                    _system_equations.result_second_equation};
    _stepper.do_step(func, x, t, dt);

    _system_equations.result_first_equation = x[0];
    _system_equations.result_second_equation = x[1];

    return _system_equations.result_first_equation;
}

void RungeKuttaBoostMethod::do_duration_step(math::decimal_t start_t,
                                             math::decimal_t end_t,
                                             math::decimal_t dt,
                                             visit_runge_func visitor) {
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

    auto func = [this](const state_type &x, state_type &dx, double t) -> void {
        math::system_of_diff_equations v_x = {x[0], x[1]};
        math::system_of_diff_equations v_dx = {dx[0], dx[1]};

        _func(v_x, v_dx, t);

        dx[0] = v_dx.result_first_equation;
        dx[1] = v_dx.result_second_equation;
    };

    auto visit = [visitor](const state_type &x, double t) -> void {
        math::system_of_diff_equations v_x = {x[0], x[1]};

        visitor(v_x, t);
    };

    state_type x = {_system_equations.result_first_equation,
                    _system_equations.result_second_equation};
    boost::numeric::odeint::integrate_const(_stepper, func, x, start_t, end_t,
                                            dt, visit);

    _system_equations.result_first_equation = x[0];
    _system_equations.result_second_equation = x[1];
}

const math::decimal_t RungeKuttaBoostMethod::kMethodEpsilon = 1e-3;

void RungeKuttaBoostMethod::init(game_manager::Config &config) const {
    config.creater_runge_kutta = [](math::runge_func func,
                                math::system_of_diff_equations start_value) {
        return std::make_unique<math::external::RungeKuttaBoostMethod>(
                std::move(func), start_value);
    };
}

}  // namespace math::external
