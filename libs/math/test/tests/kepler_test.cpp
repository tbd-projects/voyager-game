#include <gtest/gtest.h>

#include <tuple>

#include <math/utilits.hpp>
#include <math/equation_kepler.hpp>

using kepler_test_tuple = std::tuple<math::decimal_t
                    , math::decimal_t, math::decimal_t>;

class EquationKeplerTest
        : public testing::TestWithParam<kepler_test_tuple> {
  public:
    EquationKeplerTest()
            : E(std::get<0>(GetParam()))
              , M(std::get<1>(GetParam()))
              , ans(std::get<2>(GetParam()))
              , equation(E, M) {
    }

  protected:
    const math::decimal_t E;
    const math::decimal_t M;
    const math::decimal_t ans;
    math::EquationKepler equation;
};

TEST_P(EquationKeplerTest, SolveTest) {
    EXPECT_PRED2(math::Utilits::is_equal, equation.solve(), ans);
}

INSTANTIATE_TEST_SUITE_P(SelectValues, EquationKeplerTest
                         , testing::Values(
        kepler_test_tuple{math::dec(0), math::dec(1.3), math::dec(1.3)}
        , kepler_test_tuple{math::dec(0), math::dec(0), math::dec(0)}
        , kepler_test_tuple{math::dec(1), math::dec(1.6), math::dec(1.6)}
        , kepler_test_tuple{math::dec(0.9999), math::dec(-0.6), math::dec(-1.59949)}
        , kepler_test_tuple{math::dec(0.0001), math::dec(1.2), math::dec(1.20009)}
        , kepler_test_tuple{math::dec(0.8), math::dec(3.14), math::dec(3.14071)}
        , kepler_test_tuple{math::dec(0.8), math::dec(-3.14), math::dec(-3.14071)}
        , kepler_test_tuple{math::dec(0.6), math::dec(3.14), math::dec(3.1406)}
        , kepler_test_tuple{math::dec(0.6), math::dec(-3.14), math::dec(-3.1406)}
        , kepler_test_tuple{math::dec(0.4), math::dec(3.14), math::dec(3.14046)}
        , kepler_test_tuple{math::dec(0.4), math::dec(-3.14), math::dec(-3.14046)}
        , kepler_test_tuple{math::dec(0.2), math::dec(3.14), math::dec(3.14027)}
        , kepler_test_tuple{math::dec(0.2), math::dec(-3.14), math::dec(-3.14027)}
        , kepler_test_tuple{math::dec(0.4), math::dec(1.67), math::dec(2.02878)}
        , kepler_test_tuple{math::dec(0.4), math::dec(-1.67), math::dec(-2.02878)}
        , kepler_test_tuple{math::dec(0.76), math::dec(2.1), math::dec(2.53393)}
        , kepler_test_tuple{math::dec(0.34), math::dec(-2.5), math::dec(-2.65807)}
        , kepler_test_tuple{math::dec(0.52), math::dec(5.98), math::dec(5.6888)}
        , kepler_test_tuple{math::dec(0.83), math::dec(-5.9), math::dec(-5.14725)}
        , kepler_test_tuple{math::dec(0.12), math::dec(4.3), math::dec(4.19567)}
        , kepler_test_tuple{math::dec(0.43), math::dec(-3.8), math::dec(-3.60702)}
        , kepler_test_tuple{math::dec(1.5), math::dec(2.1), math::dec(1.64632)}
        , kepler_test_tuple{math::dec(1.2), math::dec(3.14), math::dec(2.1981)}
        , kepler_test_tuple{math::dec(10), math::dec(0.001), math::dec(0.000111111)}
        , kepler_test_tuple{math::dec(20), math::dec(-1.5), math::dec(-0.0788613)}
        , kepler_test_tuple{math::dec(100), math::dec(4.2), math::dec(0.0424114)}
        , kepler_test_tuple{math::dec(2), math::dec(-5.1), math::dec(-1.97612)}
        , kepler_test_tuple{math::dec(2), math::dec(0), math::dec(0)}
        , kepler_test_tuple{math::dec(1.0001), math::dec(3.2), math::dec(2.42873)}
        , kepler_test_tuple{math::dec(10000), math::dec(2.1), math::dec(0.000210021)})
);
