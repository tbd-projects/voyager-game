//
// Модуль Ветошкина Артёма
//

#include <gtest/gtest.h>

#include <tuple>
#include <debug/exception.hpp>
#include <math_imported/utilits.hpp>


using runge_kutta_test_tuple = std::tuple<math::runge_func,
        math::coords_t, math::decimal_t, math::decimal_t, math::decimal_t>;

class RungeKuttaTestOneStep
        : public testing::TestWithParam<runge_kutta_test_tuple> {
  public:
    RungeKuttaTestOneStep()
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

TEST_P(RungeKuttaTestOneStep, BaseStep) {
    auto is_equal = [] (math::decimal_t v_1, math::decimal_t v_2) -> bool {
        return std::abs(v_1 - v_2)
        < math::external::RungeKuttaBoostMethod::method_epsilon;
    };
    EXPECT_PRED2(is_equal, method.do_step(t, dt), answer);
}

INSTANTIATE_TEST_SUITE_P(SelectValues, RungeKuttaTestOneStep
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
        }, math::coords_t(1, 2), 0., 1., M_E * M_E},
        runge_kutta_test_tuple{[](const math::coords_t &x
                                  , math::coords_t &dx
                                  , math::decimal_t t) -> void {
            dx.x = x.y;
            dx.y = 4 * x.x;
        }, math::coords_t(1, 2), 0., 0.5, M_E},
        runge_kutta_test_tuple{[](const math::coords_t &x
                                  , math::coords_t &dx
                                  , math::decimal_t t) -> void {
            dx.x = x.y;
            dx.y = 4 * x.x - 3 * x.y;
        }, math::coords_t(1, 1), 0., 0., 1},
        runge_kutta_test_tuple{[](const math::coords_t &x
                                  , math::coords_t &dx
                                  , math::decimal_t t) -> void {
            dx.x = x.y;
            dx.y = 4 * x.x - 3 * x.y;
        }, math::coords_t(1, 1), 0., 1., M_E},
        runge_kutta_test_tuple{[](const math::coords_t &x
                                  , math::coords_t &dx
                                  , math::decimal_t t) -> void {
            dx.x = x.y;
            dx.y = 4 * x.x - 3 * x.y;
        }, math::coords_t(1, 1), 0., 2., M_E * M_E},
        runge_kutta_test_tuple{[](const math::coords_t &x
                                  , math::coords_t &dx
                                  , math::decimal_t t) -> void {
            dx.x = x.y;
            dx.y = t * x.y - 2 * t * x.x + 0.8;
        }, math::coords_t(-0.2, 2), 1.5, 0.1, 0.0225},
        runge_kutta_test_tuple{[](const math::coords_t &x
                                  , math::coords_t &dx
                                  , math::decimal_t t) -> void {
            dx.x = x.y;
            dx.y = t * x.y - 2 * t * x.x + 0.8;
        }, math::coords_t(-0.2, 2), 1.5, 0.2, 0.2914},
        runge_kutta_test_tuple{[](const math::coords_t &x
                                  , math::coords_t &dx
                                  , math::decimal_t t) -> void {
            dx.x = x.y;
            dx.y = t * x.y - 2 * t * x.x + 0.8;
        }, math::coords_t(0.0225, 2.4535), 1.6, 0.1, 0.2914}
));

using runge_kutta_test_tuple_loop = std::tuple<math::runge_func,
        math::coords_t, math::decimal_t
        , math::decimal_t, math::decimal_t, math::decimal_t>;

class RungeKuttaTestLoop
        : public testing::TestWithParam<runge_kutta_test_tuple_loop> {
  public:
    RungeKuttaTestLoop()
            : method(std::get<0>(GetParam()), std::get<1>(GetParam()))
              , start_t(std::get<2>(GetParam()))
              , end_t(std::get<3>(GetParam()))
              , dt(std::get<4>(GetParam()))
              , answer(std::get<5>(GetParam())) {}

  protected:
    math::external::RungeKuttaBoostMethod method;
    const math::decimal_t start_t;
    const math::decimal_t end_t;
    const math::decimal_t dt;
    const math::decimal_t answer;
};

TEST_P(RungeKuttaTestLoop, BigStep) {
    auto is_equal = [] (math::decimal_t v_1, math::decimal_t v_2) -> bool {
        return std::abs(v_1 - v_2)
               < math::external::RungeKuttaBoostMethod::method_epsilon;
    };

    size_t visited = 0;
    auto visitor = [&visited](const math::coords_t& x, math::decimal_t t) {
        visited++;
    };
    method.do_duration_step(start_t, end_t, dt, visitor);
    EXPECT_PRED2(is_equal, method.get_start_x().x, answer);

    EXPECT_EQ(visited, std::round((end_t - start_t) / dt) + 1);
}

INSTANTIATE_TEST_SUITE_P(SelectValues, RungeKuttaTestLoop
                         , testing::Values(
        runge_kutta_test_tuple_loop{[](const math::coords_t &x
                                  , math::coords_t &dx
                                  , math::decimal_t t) -> void {
            dx.x = x.y;
            dx.y = 4 * x.x;
        }, math::coords_t(1, 2), 0., 0., 0.1, 1},
        runge_kutta_test_tuple_loop{[](const math::coords_t &x
                                  , math::coords_t &dx
                                  , math::decimal_t t) -> void {
            dx.x = x.y;
            dx.y = 4 * x.x;
        }, math::coords_t(1, 2), 0., 1., 0.2, M_E * M_E},
        runge_kutta_test_tuple_loop{[](const math::coords_t &x
                                  , math::coords_t &dx
                                  , math::decimal_t t) -> void {
            dx.x = x.y;
            dx.y = 4 * x.x;
        }, math::coords_t(1, 2), 0., 0.5, 0.1, M_E},
        runge_kutta_test_tuple_loop{[](const math::coords_t &x
                                  , math::coords_t &dx
                                  , math::decimal_t t) -> void {
            dx.x = x.y;
            dx.y = 4 * x.x - 3 * x.y;
        }, math::coords_t(1, 1), 0., 1., 0.2, M_E},
        runge_kutta_test_tuple_loop{[](const math::coords_t &x
                                  , math::coords_t &dx
                                  , math::decimal_t t) -> void {
            dx.x = x.y;
            dx.y = 4 * x.x - 3 * x.y;
        }, math::coords_t(1, 1), 0., 2., 1., M_E * M_E},
        runge_kutta_test_tuple_loop{[](const math::coords_t &x
                                  , math::coords_t &dx
                                  , math::decimal_t t) -> void {
            dx.x = x.y;
            dx.y = t * x.y - 2 * t * x.x + 0.8;
        }, math::coords_t(-0.2, 2), 1.5, 1.7, 0.1, 0.2914},
        runge_kutta_test_tuple_loop{[](const math::coords_t &x
                                       , math::coords_t &dx
                                       , math::decimal_t t) -> void {
            dx.x = x.y;
            dx.y = t * x.y - 2 * t * x.x + 0.8;
        }, math::coords_t(-0.2, 2), 1.5, 1.7, 0.05, 0.2914},
        runge_kutta_test_tuple_loop{[](const math::coords_t &x
                                       , math::coords_t &dx
                                       , math::decimal_t t) -> void {
            dx.x = x.y;
            dx.y = t * x.y - 2 * t * x.x + 0.8;
        }, math::coords_t(-0.2, 2), 1.5, 1.7, 0.2, 0.2914}
));

TEST(RungeKuttaTest, TestException) {
    math::external::RungeKuttaBoostMethod tmp({}, {});
    EXPECT_THROW(tmp.do_step(2, -10), debug::ArgumentException);
    EXPECT_THROW(tmp.do_duration_step(1, 2, -10, {}), debug::ArgumentException);
    EXPECT_THROW(tmp.do_duration_step(2, 1, -10, {}), debug::ArgumentException);
    EXPECT_THROW(tmp.do_duration_step(1, 2, 0, {}), debug::ArgumentException);
    EXPECT_THROW(tmp.do_duration_step(-1, -2, 2, {}), debug::ArgumentException);
    EXPECT_THROW(tmp.do_duration_step(1, -2, -10, {})
                 , debug::ArgumentException);
}
