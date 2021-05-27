//
// Модуль Ветошкина Артёма
//

#include <gtest/gtest.h>

#include <tuple>
#include <debug/exception.hpp>
#include <physics/mechanic.hpp>


using newton_force_test_tuple = std::tuple<size_t,
        math::coords_t, math::Vector2d, size_t,
        math::coords_t, math::Vector2d, math::Vector2d>;

class NewtonForce
        : public testing::TestWithParam<newton_force_test_tuple> {
  public:
    NewtonForce()
            : first(std::make_unique<math::CirclePolygon>()
                    , std::get<1>(GetParam()), std::get<2>(GetParam())
                    , std::get<0>(GetParam()))
              , second(std::make_unique<math::CirclePolygon>()
                       , std::get<4>(GetParam()), std::get<5>(GetParam())
                       , std::get<3>(GetParam()))
              , answer(std::get<6>(GetParam()))
              , force() {}

  protected:
    physics::PhysicalObject first;
    physics::PhysicalObject second;
    const math::Vector2d answer;
    physics::NewtonForce force;
};

TEST_P(NewtonForce, TestForce) {
    EXPECT_PRED2(math::Utilits::is_equal
                 , force.get_force(first, second).get_coords().x
                 , answer.get_coords().x);
    EXPECT_PRED2(math::Utilits::is_equal
                 , force.get_force(first, second).get_coords().y
                 , answer.get_coords().y);
}

INSTANTIATE_TEST_SUITE_P(SelectValues, NewtonForce
                         , testing::Values(
        newton_force_test_tuple{1, math::coords_t(1, 2),
                                math::Vector2d(math::coords_t()), 100,
                                math::coords_t(1, 5),
                                math::Vector2d(math::coords_t()),
                                math::Vector2d(
                                        math::coords_t(0, 0.000741556))},
        newton_force_test_tuple{1, math::coords_t(1, 5),
                                math::Vector2d(math::coords_t()), 100,
                                math::coords_t(1, 2),
                                math::Vector2d(math::coords_t()),
                                math::Vector2d(
                                        math::coords_t(0, -0.000741556))}
));

