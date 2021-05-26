#pragma once

#include <math/vector2d.hpp>
#include <math/interface.hpp>
#include <boost/numeric/odeint.hpp>


namespace math::external {

typedef std::vector<math::decimal_t> state_type;


class RungeKuttaBoostMethod : public IRungeKuttaMethod {
  public:
    using stepper_type
    = boost::numeric::odeint::runge_kutta_fehlberg78<state_type>;

    RungeKuttaBoostMethod(runge_func func, math::coords_t start_x);

    math::decimal_t do_step(math::decimal_t t, math::decimal_t dt) override;

    void do_duration_step(math::decimal_t start_t, math::decimal_t end_t
                          , math::decimal_t dt
                          , visit_runge_func visitor) override;

    static const math::decimal_t method_epsilon;

  private:
    stepper_type _stepper;
};

}  // namespace math::external
