#pragma once

#include <math/interface.hpp>
#include <boost/numeric/odeint.hpp>

#include <boost/numeric/odeint/stepper/dense_output_runge_kutta.hpp>


namespace math::external {

typedef std::vector<double> state_type;

class RungeKuttaBoostMethod : public IRungeKuttaMethod {
  public:
    using stepper_type = boost::numeric::odeint::runge_kutta4_classic<state_type>;

    RungeKuttaBoostMethod(runge_func func, math::coords_t start_x);

    math::decimal_t do_step(math::decimal_t t, math::decimal_t dt) override;

    void do_duration_step(math::decimal_t start_t, math::decimal_t end_t
                          , math::decimal_t dt
                          , visit_runge_func visitor) override;

  private:
    stepper_type _stepper;
};

}  // namespace math
