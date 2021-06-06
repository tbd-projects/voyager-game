#include <gtest/gtest.h>

#include <tuple>
#include <debug/exception.hpp>
#include <physics/mechanic.hpp>

struct newton_force_test {
    size_t weight_first_object;
    math::coords_t pos_first_object;
    math::Vector2d velocity_first_object;
    size_t weight_second_object;
    math::coords_t pos_second_object;
    math::Vector2d velocity_second_object;
    math::Vector2d answer;
};

using newton_force_test_tuple = std::tuple<size_t,
        math::coords_t, math::Vector2d, size_t,
        math::coords_t, math::Vector2d, math::Vector2d>;

class NewtonForce
        : public testing::TestWithParam<newton_force_test> {
  public:
    NewtonForce()
            : parameters(GetParam())
              , first_object(std::make_unique<math::CirclePolygon>(),
                             parameters.pos_first_object,
                             parameters.velocity_first_object,
                             parameters.weight_first_object)
              , second_object(std::make_unique<math::CirclePolygon>(),
                              parameters.pos_second_object,
                              parameters.velocity_second_object,
                              parameters.weight_second_object)
              , force() {}

  protected:
    newton_force_test parameters;
    physics::PhysicalObject first_object;
    physics::PhysicalObject second_object;
    physics::NewtonForce force;
};

TEST_P(NewtonForce, TestForce) {
    EXPECT_PRED2(math::Utilits::is_equal,
                 force.get_force(first_object, second_object).get_coords().x,
                 parameters.answer.get_coords().x);
    EXPECT_PRED2(math::Utilits::is_equal,
                 force.get_force(first_object, second_object).get_coords().y,
                 parameters.answer.get_coords().y);
}

// =============================================================================
// тест проверки силы всемирного тегатения
// для более подробного изучения можно почитать тут:
// https://ru.wikipedia.org/wiki/Классическая_теория_тяготения_Ньютона
// ============================================================================

INSTANTIATE_TEST_SUITE_P(SelectValues, NewtonForce, testing::Values(
        newton_force_test{1, math::coords_t(1, 2),
                          math::Vector2d(math::coords_t()), 100,
                          math::coords_t(1, 5),
                          math::Vector2d(math::coords_t()),
                          math::Vector2d(math::coords_t(0, 0.000741556))},
        newton_force_test{1, math::coords_t(1, 5),
                          math::Vector2d(math::coords_t()), 100,
                          math::coords_t(1, 2),
                          math::Vector2d(math::coords_t()),
                          math::Vector2d(math::coords_t(0, -0.000741556))}
));

