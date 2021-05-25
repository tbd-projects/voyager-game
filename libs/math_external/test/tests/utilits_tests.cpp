#include <gtest/gtest.h>

#include <tuple>

#include <math_imported/utilits.hpp>


using runge_kutta_test_tuple = std::tuple<math::runge_func,
        math::coords_t, math::decimal_t, math::decimal_t, math::decimal_t>;

class RungeKuttaTest
        : public testing::TestWithParam<runge_kutta_test_tuple> {
  public:
    RungeKuttaTest()
            : method(std::get<0>(GetParam()), std::get<1>(GetParam()))
              , t(std::get<2>(GetParam()))
              , dt(std::get<3>(GetParam()))
              , answer(std::get<4>(GetParam())) {}

  protected:
    math::external::RungeKuttaBoostMethod method;
    const math::decimal_t t;
    const math::decimal_t dt;
    const math::decimal_t answer;
};

TEST_P(RungeKuttaTest, BaseStep) {
    EXPECT_PRED2(math::Utilits::is_equal, method.do_step(t, dt), answer);
}

INSTANTIATE_TEST_SUITE_P(SelectValues, RungeKuttaTest
                         , testing::Values(
        runge_kutta_test_tuple{[](const math::coords_t &x
                                  , math::coords_t &dx
                                  , math::decimal_t t) -> void {
            dx.x = x.y;
            dx.y = 4 * x.x;
        }, math::coords_t(1, 2), 0., 0., 1},
        runge_kutta_test_tuple{[](const math::coords_t &x
                                  , math::coords_t &dx
                                  , math::decimal_t t) -> void {
            dx.x = x.y;
            dx.y = 4 * x.x;
        }, math::coords_t(1, 2), 0., 0., 1}
));

