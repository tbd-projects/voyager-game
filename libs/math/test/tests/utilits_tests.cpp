#include <gtest/gtest.h>

#include <tuple>

#include <math/utilits.hpp>
#include <math/vector2d.hpp>

using rotate_test_tuple = std::tuple<math::coords_t, math::decimal_t
                                    , math::coords_t, math::coords_t>;

class GeometryRotateTest
        : public testing::TestWithParam<rotate_test_tuple> {
  public:
    GeometryRotateTest()
            : point(std::get<0>(GetParam()))
              , basis(std::get<2>(GetParam()))
              , angle(std::get<1>(GetParam()))
              , answer(std::get<3>(GetParam())) {}

  protected:
    const math::coords_t point;
    const math::coords_t basis;
    const math::decimal_t angle;
    const math::coords_t answer;
    math::GeometryFunction geometry;
};

TEST_P(GeometryRotateTest, FunctionRotate) {
    math::coords_t ans = geometry.rotate_point(point, angle, basis);
    EXPECT_PRED2(math::Utilits::is_equal, ans.x, answer.x);
    EXPECT_PRED2(math::Utilits::is_equal, ans.y, answer.y);
}

INSTANTIATE_TEST_SUITE_P(SelectValues, GeometryRotateTest
                         , testing::Values(
        rotate_test_tuple{
                math::coords_t(10, 0.f), 360., math::coords_t(0, 0),
                math::coords_t(10, 0.f)
        }
        , rotate_test_tuple{
                math::coords_t(10, 0), -360., math::coords_t(0, 0),
                math::coords_t(10, 0.f)
        }
        , rotate_test_tuple{
                math::coords_t(10, 0), 180., math::coords_t(0, 0),
                math::coords_t(-10, 0.f)
        }
        , rotate_test_tuple{
                math::coords_t(10, 0), -180., math::coords_t(0, 0),
                math::coords_t(-10, 0.f)
        }
        , rotate_test_tuple{
                math::coords_t(10, 0), 90., math::coords_t(0, 0),
                math::coords_t(0.f, 10)
        }
        , rotate_test_tuple{
                math::coords_t(10, 0), -90., math::coords_t(0, 0),
                math::coords_t(0.f, -10)
        }
        , rotate_test_tuple{
                math::coords_t(10, 0), 65., math::coords_t(0, 0),
                math::coords_t(4.22618, 9.06308)
        }
        , rotate_test_tuple{
                math::coords_t(10, 0), -65., math::coords_t(0, 0),
                math::coords_t(4.22618, -9.06308)
        }
        , rotate_test_tuple{
                math::coords_t(10, 0), 360., math::coords_t(12, 30),
                math::coords_t(10, 0.f)
        }
        , rotate_test_tuple{
                math::coords_t(10, 0), -360., math::coords_t(12, 30),
                math::coords_t(10, 0.f)
        }
        , rotate_test_tuple{
                math::coords_t(10, 0), 180., math::coords_t(12, 30),
                math::coords_t(14, 60)
        }
        , rotate_test_tuple{
                math::coords_t(10, 0), -180., math::coords_t(12, 30),
                math::coords_t(14, 60)
        }
        , rotate_test_tuple{
                math::coords_t(10, 0), 90., math::coords_t(12, 30),
                math::coords_t(42, 28)
        }
        , rotate_test_tuple{
                math::coords_t(10, 0), -90., math::coords_t(12, 30),
                math::coords_t(-18, 32)
        }
        , rotate_test_tuple{
                math::coords_t(10, 0), 65., math::coords_t(12, 30),
                math::coords_t(38.34399, 15.50883)
        }
        , rotate_test_tuple{
                math::coords_t(10, 0), -65., math::coords_t(12, 30),
                math::coords_t(-16.03447, 19.13406)
        }));

using relative_line_test_tuple = std::tuple<math::Vector2d, math::coords_t
        , math::coords_t, math::GeometryFunction::point_relative>;

class GeometryRelativeLineTest
: public testing::TestWithParam<relative_line_test_tuple> {
  public:
    GeometryRelativeLineTest()
            : line(std::get<0>(GetParam()))
              , start_line(std::get<1>(GetParam()))
              , point(std::get<2>(GetParam()))
              , answer(std::get<3>(GetParam())) {}

  protected:
    const math::Vector2d line;
    const math::coords_t start_line;
    const math::coords_t point;
    const math::GeometryFunction::point_relative answer;
    math::GeometryFunction geometry;
};

TEST_P(GeometryRelativeLineTest, FunctionRelativeLine) {
    if (answer == math::GeometryFunction::point_relative::at_left) {
        EXPECT_EQ(geometry.point_relative_line(line, start_line, point), answer)
                            << ">> "
                            << "Expected that point will be defined to the "
                               "left of the line";
    } else if (answer == math::GeometryFunction::point_relative::at_right) {
        EXPECT_EQ(geometry.point_relative_line(line, start_line, point), answer)
                            << ">> "
                            << "Expected that point will defined be to the "
                               "right of the line";
    } else {
        EXPECT_EQ(geometry.point_relative_line(line, start_line, point), answer)
                            << ">> "
                            << "Expected that point will defined on line";
    }
}

INSTANTIATE_TEST_SUITE_P(SelectValues, GeometryRelativeLineTest
                         , testing::Values(
        relative_line_test_tuple{
                math::Vector2d(math::coords_t(-4, 3)), math::coords_t(4, 0),
                math::coords_t(-1, 1),
                math::GeometryFunction::point_relative::at_left
        }
        , relative_line_test_tuple{
                math::Vector2d(math::coords_t(-4, 3)), math::coords_t(4, 0),
                math::coords_t(1.64, 4.52),
                math::GeometryFunction::point_relative::at_right
        }
        , relative_line_test_tuple{
                math::Vector2d(math::coords_t(-4, 3)), math::coords_t(4, 0),
                math::coords_t(8, -3),
                math::GeometryFunction::point_relative::on_line
        }
        , relative_line_test_tuple{
                math::Vector2d(math::coords_t(-4, 3)), math::coords_t(4, 0),
                math::coords_t(-4, 6),
                math::GeometryFunction::point_relative::on_line
        }
        , relative_line_test_tuple{
                math::Vector2d(math::coords_t(-4, 3)), math::coords_t(4, 0),
                math::coords_t(2, -10),
                math::GeometryFunction::point_relative::at_left
        }
        , relative_line_test_tuple{
                math::Vector2d(math::coords_t(-4, 3)), math::coords_t(4, 0),
                math::coords_t(10, 1),
                math::GeometryFunction::point_relative::at_right
        }
        , relative_line_test_tuple{
                math::Vector2d(math::coords_t(4, -3)), math::coords_t(0, 3),
                math::coords_t(10, 1),
                math::GeometryFunction::point_relative::at_left
        }
        , relative_line_test_tuple{
                math::Vector2d(math::coords_t(4, -3)), math::coords_t(0, 3),
                math::coords_t(2, -10),
                math::GeometryFunction::point_relative::at_right
        }
        , relative_line_test_tuple{
                math::Vector2d(math::coords_t(4, -3)), math::coords_t(0, 3),
                math::coords_t(-4, 6),
                math::GeometryFunction::point_relative::on_line
        }
        , relative_line_test_tuple{
                math::Vector2d(math::coords_t(4, -3)), math::coords_t(0, 3),
                math::coords_t(1.64, 4.52),
                math::GeometryFunction::point_relative::at_left
        }
        , relative_line_test_tuple{
                math::Vector2d(math::coords_t(4, -3)), math::coords_t(0, 3),
                math::coords_t(-1, 1),
                math::GeometryFunction::point_relative::at_right
        }
        , relative_line_test_tuple{
                math::Vector2d(math::coords_t(4, -3)), math::coords_t(0, 3),
                math::coords_t(8, -3),
                math::GeometryFunction::point_relative::on_line
        }));
