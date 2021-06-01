#include <gtest/gtest.h>

#include <tuple>

#include <math/utilits.hpp>
#include <math/equation_kepler.hpp>

struct kepler_test {
    math::decimal_t e;
    math::decimal_t M;
    math::decimal_t answer;
};

class EquationKeplerTest
        : public testing::TestWithParam<kepler_test> {
  public:
    EquationKeplerTest()
            : parameters(GetParam())
              , equation(parameters.e, parameters.M) {
    }

  protected:
    kepler_test parameters;
    math::EquationKepler equation;
};

TEST_P(EquationKeplerTest, SolveTest) {
    EXPECT_PRED2(math::Utilits::is_equal, equation.solve(), parameters.answer);
}

// =============================================================================
// тест решения уравнения Кеплера
// e - эксцентриситет орбиты
// M -  средняя аномалия
// Answer - результат решения эксцентрическая аномалия(E)
// для более подробного изучения можно почитать тут:
// https://ru.wikipedia.org/wiki/Уравнение_Кеплера
// =============================================================================

INSTANTIATE_TEST_SUITE_P(SelectValues, EquationKeplerTest, testing::Values(
        kepler_test{math::decm(0), math::decm(1.3), math::decm(1.3)},
        kepler_test{math::decm(0), math::decm(0), math::decm(0)},
        kepler_test{math::decm(1), math::decm(1.6), math::decm(1.6)},
        kepler_test{math::decm(0.9999), math::decm(-0.6),
                          math::decm(-1.59949)},
        kepler_test{math::decm(0.0001), math::decm(1.2),
                          math::decm(1.20009)},
        kepler_test{math::decm(0.8), math::decm(3.14),
                          math::decm(3.14071)},
        kepler_test{math::decm(0.8), math::decm(-3.14),
                          math::decm(-3.14071)},
        kepler_test{math::decm(0.6), math::decm(3.14),
                          math::decm(3.1406)},
        kepler_test{math::decm(0.6), math::decm(-3.14),
                          math::decm(-3.1406)},
        kepler_test{math::decm(0.4), math::decm(3.14),
                          math::decm(3.14046)},
        kepler_test{math::decm(0.4), math::decm(-3.14),
                          math::decm(-3.14046)},
        kepler_test{math::decm(0.2), math::decm(3.14),
                          math::decm(3.14027)},
        kepler_test{math::decm(0.2), math::decm(-3.14),
                          math::decm(-3.14027)},
        kepler_test{math::decm(0.4), math::decm(1.67),
                          math::decm(2.02878)},
        kepler_test{math::decm(0.4), math::decm(-1.67),
                          math::decm(-2.02878)},
        kepler_test{math::decm(0.76), math::decm(2.1),
                          math::decm(2.53393)},
        kepler_test{math::decm(0.34), math::decm(-2.5),
                          math::decm(-2.65807)},
        kepler_test{math::decm(0.52), math::decm(5.98),
                          math::decm(5.6888)},
        kepler_test{math::decm(0.83), math::decm(-5.9),
                          math::decm(-5.14725)},
        kepler_test{math::decm(0.12), math::decm(4.3),
                          math::decm(4.19567)},
        kepler_test{math::decm(0.43), math::decm(-3.8),
                          math::decm(-3.60702)},
        kepler_test{math::decm(1.5), math::decm(2.1),
                          math::decm(1.64632)},
        kepler_test{math::decm(1.2), math::decm(3.14),
                          math::decm(2.1981)},
        kepler_test{math::decm(10), math::decm(0.001),
                          math::decm(0.000111111)},
        kepler_test{math::decm(20), math::decm(-1.5),
                          math::decm(-0.0788613)},
        kepler_test{math::decm(100), math::decm(4.2),
                          math::decm(0.0424114)},
        kepler_test{math::decm(2), math::decm(-5.1),
                          math::decm(-1.97612)},
        kepler_test{math::decm(2), math::decm(0),
                          math::decm(0)},
        kepler_test{math::decm(1.0001), math::decm(3.2),
                          math::decm(2.42873)},
        kepler_test{math::decm(10000), math::decm(2.1),
                          math::decm(0.000210021)})
);
