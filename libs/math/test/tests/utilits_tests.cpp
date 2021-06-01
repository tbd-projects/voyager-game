#include <gtest/gtest.h>

#include <tuple>

#include <math/utilits.hpp>
#include <math/vector2d.hpp>

struct rotate_test {
    math::coords_t point;
    math::decimal_t angle;
    math::coords_t basis;
    math::coords_t answer;
};

class GeometryRotateTest
        : public testing::TestWithParam<rotate_test> {
  public:
    GeometryRotateTest()
            : parameters(GetParam()) {}

  protected:
    rotate_test parameters;
    math::GeometryFunction geometry;
};

TEST_P(GeometryRotateTest, FunctionRotate) {
    math::coords_t ans = geometry.rotate_point(parameters.point,
                                               parameters.angle,
                                               parameters.basis);
    EXPECT_PRED2(math::Utilits::is_equal, ans.x, parameters.answer.x);
    EXPECT_PRED2(math::Utilits::is_equal, ans.y, parameters.answer.y);
}

// =============================================================================
// тест проверки функции поворота точки вокруг базиса
// point - точка, которую поворачиваем
// angle - угол поворота (положительный -> ппротив часовой стрелки)
// basis - базис вокруг которого поворачиваем
// answer - значение x при котором заданная функция обращается в ноль
// для более подробного изучения можно почитать тут:
// https://ru.xcv.wiki/wiki/Rotation_matrix
// =============================================================================

INSTANTIATE_TEST_SUITE_P(SelectValues, GeometryRotateTest, testing::Values(
        rotate_test{
                math::coords_t(10, 0.f), 360., math::coords_t(0, 0),
                math::coords_t(10, 0.f)
        }, rotate_test{
                math::coords_t(10, 0), -360., math::coords_t(0, 0),
                math::coords_t(10, 0.f)
        }, rotate_test{
                math::coords_t(10, 0), 180., math::coords_t(0, 0),
                math::coords_t(-10, 0.f)
        }, rotate_test{
                math::coords_t(10, 0), -180., math::coords_t(0, 0),
                math::coords_t(-10, 0.f)
        }, rotate_test{
                math::coords_t(10, 0), 90., math::coords_t(0, 0),
                math::coords_t(0.f, 10)
        }, rotate_test{
                math::coords_t(10, 0), -90., math::coords_t(0, 0),
                math::coords_t(0.f, -10)
        }, rotate_test{
                math::coords_t(10, 0), 65., math::coords_t(0, 0),
                math::coords_t(4.22618, 9.06308)
        }, rotate_test{
                math::coords_t(10, 0), -65., math::coords_t(0, 0),
                math::coords_t(4.22618, -9.06308)
        }, rotate_test{
                math::coords_t(10, 0), 360., math::coords_t(12, 30),
                math::coords_t(10, 0.f)
        }, rotate_test{
                math::coords_t(10, 0), -360., math::coords_t(12, 30),
                math::coords_t(10, 0.f)
        }, rotate_test{
                math::coords_t(10, 0), 180., math::coords_t(12, 30),
                math::coords_t(14, 60)
        }, rotate_test{
                math::coords_t(10, 0), -180., math::coords_t(12, 30),
                math::coords_t(14, 60)
        }, rotate_test{
                math::coords_t(10, 0), 90., math::coords_t(12, 30),
                math::coords_t(42, 28)
        }, rotate_test{
                math::coords_t(10, 0), -90., math::coords_t(12, 30),
                math::coords_t(-18, 32)
        }, rotate_test{
                math::coords_t(10, 0), 65., math::coords_t(12, 30),
                math::coords_t(38.34399, 15.50883)
        }, rotate_test{
                math::coords_t(10, 0), -65., math::coords_t(12, 30),
                math::coords_t(-16.03447, 19.13406)
        }));


struct relative_line_test {
    math::Vector2d line;
    math::coords_t start_line;
    math::coords_t point;
    math::GeometryFunction::point_relative answer;
};

class GeometryRelativeLineTest
        : public testing::TestWithParam<relative_line_test> {
  public:
    GeometryRelativeLineTest()
            : parameters(GetParam()) {}

  protected:
    relative_line_test parameters;
    math::GeometryFunction geometry;
};

TEST_P(GeometryRelativeLineTest, FunctionRelativeLine) {
    if (parameters.answer == math::GeometryFunction::point_relative::at_left) {
        EXPECT_EQ(geometry.point_relative_line(parameters.line,
                                               parameters.start_line,
                                               parameters.point),
                  parameters.answer)
                            << ">> "
                            << "Expected that point will be defined to the "
                               "left of the line";
    } else if (parameters.answer ==
               math::GeometryFunction::point_relative::at_right) {
        EXPECT_EQ(geometry.point_relative_line(parameters.line,
                                               parameters.start_line,
                                               parameters.point),
                  parameters.answer)
                            << ">> "
                            << "Expected that point will defined be to the "
                               "right of the line";
    } else {
        EXPECT_EQ(geometry.point_relative_line(parameters.line,
                                               parameters.start_line,
                                               parameters.point),
                  parameters.answer)
                            << ">> "
                            << "Expected that point will defined on line";
    }
}

// =============================================================================
// тест проверки метода опредления положения точки относительно прямой
// line - вектор соответствующий направлению прямой
// start_line - любоя точка прямой
// point - точка положение которой проверяется
// answer - положоние точки относительно прямой,
//         если смотреть на неё по направлению вектора: слева, справа, на прямой
// для более подробного изучения можно почитать тут:
// https://habr.com/ru/post/148325/ (задача №1)
// =============================================================================

INSTANTIATE_TEST_SUITE_P(SelectValues, GeometryRelativeLineTest,
                         testing::Values(
                     relative_line_test{
                             math::Vector2d(math::coords_t(-4, 3)),
                             math::coords_t(4, 0),
                             math::coords_t(-1, 1),
                             math::GeometryFunction::point_relative::at_left
                     }, relative_line_test{
                             math::Vector2d(math::coords_t(-4, 3)),
                             math::coords_t(4, 0),
                             math::coords_t(1.64, 4.52),
                             math::GeometryFunction::point_relative::at_right
                     }, relative_line_test{
                             math::Vector2d(math::coords_t(-4, 3)),
                             math::coords_t(4, 0),
                             math::coords_t(8, -3),
                             math::GeometryFunction::point_relative::on_line
                     }, relative_line_test{
                             math::Vector2d(math::coords_t(-4, 3)),
                             math::coords_t(4, 0),
                             math::coords_t(-4, 6),
                             math::GeometryFunction::point_relative::on_line
                     }, relative_line_test{
                             math::Vector2d(math::coords_t(-4, 3)),
                             math::coords_t(4, 0),
                             math::coords_t(2, -10),
                             math::GeometryFunction::point_relative::at_left
                     }, relative_line_test{
                             math::Vector2d(math::coords_t(-4, 3)),
                             math::coords_t(4, 0),
                             math::coords_t(10, 1),
                             math::GeometryFunction::point_relative::at_right
                     }, relative_line_test{
                             math::Vector2d(math::coords_t(4, -3)),
                             math::coords_t(0, 3),
                             math::coords_t(10, 1),
                             math::GeometryFunction::point_relative::at_left
                     }, relative_line_test{
                             math::Vector2d(math::coords_t(4, -3)),
                             math::coords_t(0, 3),
                             math::coords_t(2, -10),
                             math::GeometryFunction::point_relative::at_right
                     }, relative_line_test{
                             math::Vector2d(math::coords_t(4, -3)),
                             math::coords_t(0, 3),
                             math::coords_t(-4, 6),
                             math::GeometryFunction::point_relative::on_line
                     }, relative_line_test{
                             math::Vector2d(math::coords_t(4, -3)),
                             math::coords_t(0, 3),
                             math::coords_t(1.64, 4.52),
                             math::GeometryFunction::point_relative::at_left
                     }, relative_line_test{
                             math::Vector2d(math::coords_t(4, -3)),
                             math::coords_t(0, 3),
                             math::coords_t(-1, 1),
                             math::GeometryFunction::point_relative::at_right
                     }, relative_line_test{
                             math::Vector2d(math::coords_t(4, -3)),
                             math::coords_t(0, 3),
                             math::coords_t(8, -3),
                             math::GeometryFunction::point_relative::on_line
                     }));

using return_alg = math::AlgebraicMethods::return_for_solve_equastion;

struct algebra_test {
    std::function<return_alg(math::decimal_t)> func;
    math::decimal_t start_x;
    size_t number_itter;
    math::decimal_t answer;
};

class AlgebraTest
        : public testing::TestWithParam<algebra_test> {
  public:
    AlgebraTest()
            : parameters(GetParam()) {}

  protected:
    algebra_test parameters;
    math::AlgebraicMethods algebra;
};

TEST_P(AlgebraTest, HalleyFunction) {
    EXPECT_PRED2(math::Utilits::is_equal,
                 algebra.solve_equastion_by_Halley(parameters.func,
                                                   parameters.start_x,
                                                   parameters.number_itter),
                 parameters.answer);
}

// =============================================================================
// тест проверки метода Галлилея поиска решения уравнения
// func - функция которая по заданному x, возвращаетя значение искодной функции,
//          для которой ищется корень, а также её первая и вторая вроизводная
// start_x - приближённое значение, от которого начинается поиск корня
// number_itter - число иттераций алгоритма
// answer - значение x при котором заданная функция обращается в ноль
// для более подробного изучения можно почитать тут:
// https://ru.xcv.wiki/wiki/Halley%27s_method
// =============================================================================

INSTANTIATE_TEST_SUITE_P(SelectValues, AlgebraTest, testing::Values(
        algebra_test{  // уравнение X^4 + x^3 + 2 * x^2 - x = 3
                [](auto x) -> return_alg {
                    return {
                            // сама функция
                            std::pow(x, 4) +
                            std::pow(x, 3) + 2. * x * x - x - 3.,
                            // её первая производная
                            4. * std::pow(x, 3)
                            + 3. * std::pow(x, 2) + 4 * x - 1,
                            // её вторая производная
                            12. * std::pow(x, 2) + 6. * x + 4
                    };
                }, math::decm(0.8), 10, math::decm(1)
        },
        algebra_test{  // уравнение X^4 + x^3 + 2 * x^2 - x = 3
                [](auto x) -> return_alg {
                    return {
                            // сама функция
                            std::pow(x, 4) + std::pow(x, 3)
                            + 2. * x * x - x - 3.,
                            // её первая производная
                            4. * std::pow(x, 3)
                            + 3. * std::pow(x, 2) + 4 * x - 1,
                            // её вторая производная
                            12. * std::pow(x, 2) + 6. * x + 4
                    };
                }, math::decm(-0.8), 5, math::decm(-1)
        },
        algebra_test{  // уравнение sqrt(2 * x + 1) = 3
                [](auto x) -> return_alg {
                    return {
                            // сама функция
                            sqrt(2 * x + 1) - 3,
                            // её первая производная
                            1 / sqrt(2 * x + 1),
                            // её вторая производная
                            -1 / ((2 * x + 1) * sqrt(2 * x + 1))};
                }, math::decm(0.1), 30, math::decm(4)
        },
        algebra_test{  // уравнение lg(x-3) + lg(x-2) = 1 + lg(5)
                [](auto x) -> return_alg {
                    return {
                            // сама функция
                            std::log10(x - 3) + std::log10(x - 2)
                            - 1 + std::log10(5),
                            // её первая производная
                            1 / ((x - 3) * std::log(10))
                            + 1 / ((x - 2) * std::log(10)),
                            // её вторая производная
                            (1 / ((x - 3) * (x - 3)) +
                             1 / ((x - 2) * (x - 2))) / std::log(10)
                    };
                }, math::decm(4.5), 25, math::decm(4)
        },
        algebra_test{  // уравнение sin(x) = 0
                [](auto x) -> return_alg {
                    return {
                            // сама функция
                            sin(x),
                            // её первая производная
                            cos(x),
                            // её вторая производная
                            -sin(x)
                    };
                }, math::decm(0.8), 3, math::decm(0)
        })
);
