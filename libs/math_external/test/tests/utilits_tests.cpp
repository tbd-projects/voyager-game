#include <gtest/gtest.h>

#include <tuple>

#include <math/utilits.hpp>
#include <math/vector2d.hpp>

/*
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
*/
