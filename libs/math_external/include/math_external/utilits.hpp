#pragma once

#include <math/vector2d.hpp>
#include <math/interface.hpp>
#include <boost/numeric/odeint.hpp>
#include <game_manager/interface.hpp>

namespace math::external {

typedef std::vector<math::decimal_t> state_type;


class RungeKuttaBoostMethod : public IRungeKuttaMethod,
        public game_manager::IInitDependencies {
  public:
    using stepper_type
    = boost::numeric::odeint::runge_kutta_fehlberg78<state_type>;

    RungeKuttaBoostMethod(runge_func func,
                          math::system_of_diff_equations start_value);

    math::decimal_t do_step(math::decimal_t t, math::decimal_t dt) override;

    void do_duration_step(math::decimal_t start_t, math::decimal_t end_t,
                          math::decimal_t dt,
                          visit_runge_func visitor) override;

    void init(game_manager::Config &config) const override;

    static const math::decimal_t kMethodEpsilon;

  private:
    stepper_type _stepper;
};

}  // namespace math::external
