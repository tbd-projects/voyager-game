#pragma once

#include <math/interface.hpp>
#include <boost/numeric/odeint.hpp>

namespace math::external {

typedef std::vector< math::decimal_t > state_type;

class RungeKuttaBoostMethod : public IRungeKuttaMethod {
  public:
    RungeKuttaBoostMethod(runge_func func, math::coords_t start_x);

    math::decimal_t do_step(math::decimal_t t, math::decimal_t dt) override;

    void do_duration_step(math::decimal_t start_t, math::decimal_t end_t
                          , math::decimal_t dt
                          , visit_runge_func visitor) override;

  private:
    boost::numeric::odeint::runge_kutta4_classic<state_type> _stepper;
};

}  // namespace math
