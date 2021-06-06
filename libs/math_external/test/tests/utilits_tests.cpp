#include <gtest/gtest.h>

#include <tuple>
#include <debug/exception.hpp>
#include <math_external/utilits.hpp>

struct runge_kutta_test {
    math::runge_func func;
    math::system_of_diff_equations start_value;
    math::decimal_t t;
    math::decimal_t dt;
    math::decimal_t answer;
};

// для фикса утечек gtest при попытки вывода данной структуры
void PrintTo(const runge_kutta_test& bar, std::ostream* os) {
    *os << bar.answer;
}

class RungeKuttaTestOneStep
        : public testing::TestWithParam<runge_kutta_test> {
  public:
    RungeKuttaTestOneStep()
            : parameters(GetParam())
              , method(parameters.func, parameters.start_value) {}

  protected:
    runge_kutta_test parameters;
    math::external::RungeKuttaBoostMethod method;
};

TEST_P(RungeKuttaTestOneStep, BaseStep) {
    auto is_equal = [](math::decimal_t v_1, math::decimal_t v_2) -> bool {
        return std::abs(v_1 - v_2)
               < math::external::RungeKuttaBoostMethod::kMethodEpsilon;
    };
    EXPECT_PRED2(is_equal, method.do_step(parameters.t, parameters.dt),
                 parameters.answer);
}

// =============================================================================
// тест решения диф уравнения методом Ранге Кутта на один шаг
// func - функция просчитывающая новые хначения для требуемой системы
//              дифференциональных уравнений первого порядка
// start_value - начальные условия задачи Коши
//                  для каждого из уравений в системе
// start_t - стартовое значение, для которого заданны начальные условия
// dt - шаг расчётов
// answer - искомое значение первого уравнения в системе
//
// В данном случае метод предназначен для решения дифф. уравнений
//  второго порядка, для метода она разбита на систему из двух дифф уравнений
//  первого  и следовательно интересует значение только первого уравнения
//  из системы, т.к. это будет сооветствовать значению второй производной
//  из исходной уравнения второго порядка
//
// для более подробного изучения можно почитать тут:
// https://ru.wikipedia.org/wiki/Метод_Рунге_—_Кутты
// http://koi.tspu.ru/koi_books/gazizov/l10p07.htm
// ============================================================================

INSTANTIATE_TEST_SUITE_P(SelectValues, RungeKuttaTestOneStep, testing::Values(
        runge_kutta_test{[](const math::system_of_diff_equations &x,
                            math::system_of_diff_equations &dx,
                            math::decimal_t t) -> void {
            dx.result_first_equation = x.result_second_equation;
            dx.result_second_equation = 4 * x.result_first_equation;
        }, math::system_of_diff_equations(1, 2), 0., 0., 1},
        runge_kutta_test{[](const math::system_of_diff_equations &x,
                            math::system_of_diff_equations &dx,
                            math::decimal_t t) -> void {
            dx.result_first_equation = x.result_second_equation;
            dx.result_second_equation = 4 * x.result_first_equation;
        }, math::system_of_diff_equations(1, 2), 0., 1., M_E * M_E},
        runge_kutta_test{[](const math::system_of_diff_equations &x,
                            math::system_of_diff_equations &dx,
                            math::decimal_t t) -> void {
            dx.result_first_equation = x.result_second_equation;
            dx.result_second_equation = 4 * x.result_first_equation;
        }, math::system_of_diff_equations(1, 2), 0., 0.5, M_E},
        runge_kutta_test{[](const math::system_of_diff_equations &x,
                            math::system_of_diff_equations &dx,
                            math::decimal_t t) -> void {
            dx.result_first_equation = x.result_second_equation;
            dx.result_second_equation = 4 * x.result_first_equation
                                        - 3 * x.result_second_equation;
        }, math::system_of_diff_equations(1, 1), 0., 0., 1},
        runge_kutta_test{[](const math::system_of_diff_equations &x,
                            math::system_of_diff_equations &dx,
                            math::decimal_t t) -> void {
            dx.result_first_equation = x.result_second_equation;
            dx.result_second_equation = 4 * x.result_first_equation
                                        - 3 * x.result_second_equation;
        }, math::system_of_diff_equations(1, 1), 0., 1., M_E},
        runge_kutta_test{[](const math::system_of_diff_equations &x,
                            math::system_of_diff_equations &dx,
                            math::decimal_t t) -> void {
            dx.result_first_equation = x.result_second_equation;
            dx.result_second_equation = 4 * x.result_first_equation
                                        - 3 * x.result_second_equation;
        }, math::system_of_diff_equations(1, 1), 0., 2., M_E * M_E},
        runge_kutta_test{[](const math::system_of_diff_equations &x,
                            math::system_of_diff_equations &dx,
                            math::decimal_t t) -> void {
            dx.result_first_equation = x.result_second_equation;
            dx.result_second_equation = t * x.result_second_equation
                                        - 2 * t * x.result_first_equation + 0.8;
        }, math::system_of_diff_equations(-0.2, 2), 1.5, 0.1, 0.0225},
        runge_kutta_test{[](const math::system_of_diff_equations &x,
                            math::system_of_diff_equations &dx,
                            math::decimal_t t) -> void {
            dx.result_first_equation = x.result_second_equation;
            dx.result_second_equation = t * x.result_second_equation
                                        - 2 * t * x.result_first_equation + 0.8;
        }, math::system_of_diff_equations(-0.2, 2), 1.5, 0.2, 0.2914},
        runge_kutta_test{[](const math::system_of_diff_equations &x,
                            math::system_of_diff_equations &dx,
                            math::decimal_t t) -> void {
            dx.result_first_equation = x.result_second_equation;
            dx.result_second_equation = t * x.result_second_equation -
                                        2 * t * x.result_first_equation + 0.8;
        }, math::system_of_diff_equations(0.0225, 2.4535), 1.6, 0.1, 0.2914}
));


struct runge_kutta_test_loop {
    math::runge_func func;
    math::system_of_diff_equations start_value;
    math::decimal_t start_t;
    math::decimal_t end_t;
    math::decimal_t dt;
    math::decimal_t answer;
};

// для фикса утечек gtest при попытки вывода данной структуры
void PrintTo(const runge_kutta_test_loop& bar, std::ostream* os) {
    *os << bar.answer;
}

class RungeKuttaTestLoop
        : public testing::TestWithParam<runge_kutta_test_loop> {
  public:
    RungeKuttaTestLoop()
            : parameters(GetParam())
              , method(parameters.func, parameters.start_value) {}

  protected:
    runge_kutta_test_loop parameters;
    math::external::RungeKuttaBoostMethod method;
};

TEST_P(RungeKuttaTestLoop, BigStep) {
    auto is_equal = [](math::decimal_t v_1, math::decimal_t v_2) -> bool {
        return std::abs(v_1 - v_2)
               < math::external::RungeKuttaBoostMethod::kMethodEpsilon;
    };

    size_t visited = 0;
    auto visitor = [&visited](const math::system_of_diff_equations &x,
                              math::decimal_t t) {
        visited++;
    };
    method.do_duration_step(parameters.start_t, parameters.end_t, parameters.dt,
                            visitor);
    EXPECT_PRED2(is_equal, method.get_result_equations().result_first_equation,
                 parameters.answer);

    EXPECT_EQ(visited, std::round(
            (parameters.end_t - parameters.start_t) / parameters.dt) + 1);
}

// =============================================================================
// тест решения диф уравнения методом Ранге Кутта через промежуток знанчений
// func - функция просчитывающая новые хначения для требуемой системы
//              дифференциональных уравнений первого порядка
// start_value - начальные условия задачи Коши
//                  для каждого из уравений в системе
// start_t - стартовое значение, для которого заданны начальные условия
// end_t - значения в котором ищется результат системы дифф. уравнений
// dt - шаг расчётов
// answer - искомое значение первого уравнения в системе
//
// В данном случае метод предназначен для решения дифф. уравнений
//  второго порядка, для метода она разбита на систему из двух дифф уравнений
//  первого  и следовательно интересует значение только первого уравнения
//  из системы, т.к. это будет сооветствовать значению второй производной
//  из исходной уравнения второго порядка
//
// для более подробного изучения можно почитать тут:
// https://ru.wikipedia.org/wiki/Метод_Рунге_—_Кутты
// http://koi.tspu.ru/koi_books/gazizov/l10p07.htm
// ============================================================================

INSTANTIATE_TEST_SUITE_P(SelectValues, RungeKuttaTestLoop, testing::Values(
        runge_kutta_test_loop{[](const math::system_of_diff_equations &x,
                                 math::system_of_diff_equations &dx,
                                 math::decimal_t t) -> void {
            dx.result_first_equation = x.result_second_equation;
            dx.result_second_equation = 4 * x.result_first_equation;
        }, math::system_of_diff_equations(1, 2), 0., 0., 0.1, 1},
        runge_kutta_test_loop{[](const math::system_of_diff_equations &x,
                                 math::system_of_diff_equations &dx,
                                 math::decimal_t t) -> void {
            dx.result_first_equation = x.result_second_equation;
            dx.result_second_equation = 4 * x.result_first_equation;
        }, math::system_of_diff_equations(1, 2), 0., 1., 0.2, M_E * M_E},
        runge_kutta_test_loop{[](const math::system_of_diff_equations &x,
                                 math::system_of_diff_equations &dx,
                                 math::decimal_t t) -> void {
            dx.result_first_equation = x.result_second_equation;
            dx.result_second_equation = 4 * x.result_first_equation;
        }, math::system_of_diff_equations(1, 2), 0., 0.5, 0.1, M_E},
        runge_kutta_test_loop{[](const math::system_of_diff_equations &x,
                                 math::system_of_diff_equations &dx,
                                 math::decimal_t t) -> void {
            dx.result_first_equation = x.result_second_equation;
            dx.result_second_equation =
                    4 * x.result_first_equation - 3 * x.result_second_equation;
        }, math::system_of_diff_equations(1, 1), 0., 1., 0.2, M_E},
        runge_kutta_test_loop{[](const math::system_of_diff_equations &x,
                                 math::system_of_diff_equations &dx,
                                 math::decimal_t t) -> void {
            dx.result_first_equation = x.result_second_equation;
            dx.result_second_equation =
                    4 * x.result_first_equation - 3 * x.result_second_equation;
        }, math::system_of_diff_equations(1, 1), 0., 2., 1., M_E * M_E},
        runge_kutta_test_loop{[](const math::system_of_diff_equations &x,
                                 math::system_of_diff_equations &dx,
                                 math::decimal_t t) -> void {
            dx.result_first_equation = x.result_second_equation;
            dx.result_second_equation = t * x.result_second_equation -
                                        2 * t * x.result_first_equation + 0.8;
        }, math::system_of_diff_equations(-0.2, 2), 1.5, 1.7, 0.1, 0.2914},
        runge_kutta_test_loop{[](const math::system_of_diff_equations &x,
                                 math::system_of_diff_equations &dx,
                                 math::decimal_t t) -> void {
            dx.result_first_equation = x.result_second_equation;
            dx.result_second_equation = t * x.result_second_equation -
                                        2 * t * x.result_first_equation + 0.8;
        }, math::system_of_diff_equations(-0.2, 2), 1.5, 1.7, 0.05, 0.2914},
        runge_kutta_test_loop{[](const math::system_of_diff_equations &x,
                                 math::system_of_diff_equations &dx,
                                 math::decimal_t t) -> void {
            dx.result_first_equation = x.result_second_equation;
            dx.result_second_equation = t * x.result_second_equation -
                                        2 * t * x.result_first_equation + 0.8;
        }, math::system_of_diff_equations(-0.2, 2), 1.5, 1.7, 0.2, 0.2914}
));

TEST(RungeKuttaTest, TestException) {
    math::external::RungeKuttaBoostMethod tmp({}, {});
    EXPECT_THROW(tmp.do_step(2, -10), debug::ArgumentException);
    EXPECT_THROW(tmp.do_duration_step(1, 2, -10, {}), debug::ArgumentException);
    EXPECT_THROW(tmp.do_duration_step(2, 1, -10, {}), debug::ArgumentException);
    EXPECT_THROW(tmp.do_duration_step(1, 2, 0, {}), debug::ArgumentException);
    EXPECT_THROW(tmp.do_duration_step(-1, -2, 2, {}), debug::ArgumentException);
    EXPECT_THROW(tmp.do_duration_step(1, -2, -10, {}),
                 debug::ArgumentException);
}
