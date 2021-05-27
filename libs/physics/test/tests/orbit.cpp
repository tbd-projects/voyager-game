#include <gtest/gtest.h>
#include <gmock/gmock.h>

#define TEST_ENGINE

#include <physics.hpp>


class MockEngine : public physics::Engine {
  public:
    MOCK_CONST_METHOD0(get_part_of_seconds_in_tick, math::decimal_t());
    MOCK_CONST_METHOD1(calc_force_by_object
                       , math::Vector2d(physics::PhysicalObject & object));
    MOCK_CONST_METHOD0(get_cals_in_tick, size_t());
};

class OrbitFixture : public testing::Test {
  public:
    OrbitFixture()
            : _kepler_orbit(std::make_unique<math::CirclePolygon>(
            math::CirclePolygon(math::coords_t(0, 0), 5))
                            , 50, {{500, 300}, {10, 10}, 0, 100})
              , _kepler_orbit_rotated(std::make_unique<math::CirclePolygon>(
                    math::CirclePolygon(math::coords_t(0, 0), 5))
                                      , 50, {{500, 300}, {10, 10}, -90, 100})
              , _newton_orbit(std::make_unique<math::CirclePolygon>(
                    math::CirclePolygon(math::coords_t(0, 0), 5))
                              , 100, math::Vector2d(0, 1), {20, 30})
              , _down_kepler_pos(math::dec(5.512388980)) {}

  protected:
    physics::AstronomicalObject _kepler_orbit;
    physics::AstronomicalObject _kepler_orbit_rotated;
    physics::AstronomicalObject _newton_orbit;
    math::decimal_t _down_kepler_pos;
};

TEST_F(OrbitFixture, kepler_test) {
    MockEngine mock_engine;

    _kepler_orbit.relocate_on_orbit(
            (math::dec(49) /
             _kepler_orbit.get_orbit().get_orbit_properties().period) *
            math::Utilits::to_grad(math::const_2_pi));

    EXPECT_CALL(mock_engine, get_part_of_seconds_in_tick()).Times(1).WillOnce(
            testing::Return(1.f));
    _kepler_orbit.move(mock_engine);

    math::decimal_t period = _kepler_orbit.get_orbit()
            .get_orbit_properties().period;
    math::decimal_t a
            = _kepler_orbit.get_orbit().get_orbit_properties().variables.x;
    math::decimal_t b
            = _kepler_orbit.get_orbit().get_orbit_properties().variables.y;
    math::decimal_t ans_y
            = _kepler_orbit.get_orbit().get_orbit_properties().basis.y
              + 2 * a - a * (1 - std::sqrt(1 - (b * b) / (a * a)));
    EXPECT_TRUE(math::Utilits::is_equal(_kepler_orbit.get_pos().x
                                        , _kepler_orbit.get_orbit()
                    .get_orbit_properties().basis.x))
                        << "Is not equal x: "
                        << _kepler_orbit.get_pos().x << " and "
                        << _kepler_orbit.get_orbit()
                                .get_orbit_properties().basis.x;
    EXPECT_TRUE(math::Utilits::is_equal(_kepler_orbit.get_pos().y, ans_y))
                        << "Is not equal y: "
                        << _kepler_orbit.get_pos().y << " and " << ans_y;

    EXPECT_CALL(mock_engine, get_part_of_seconds_in_tick()).Times(1).WillOnce(
            testing::Return((_down_kepler_pos / math::const_2_pi)
                            * period - period / math::dec(2)));
    _kepler_orbit.move(mock_engine);

    ans_y = ans_y - a;
    EXPECT_TRUE(math::Utilits::is_equal(_kepler_orbit.get_pos().x,
            _kepler_orbit.get_orbit().get_orbit_properties().basis.x - b))
                        << "Is not equal x: "
                        << _kepler_orbit.get_pos().x << " and " <<
                        _kepler_orbit.get_orbit()
                                .get_orbit_properties().basis.x - b;
    EXPECT_TRUE(math::Utilits::is_equal(_kepler_orbit.get_pos().y, ans_y))
                        << "Is not equal y: "
                        << _kepler_orbit.get_pos().y << " and "
                        << ans_y;
}

TEST_F(OrbitFixture, kepler_test_with_rotate_orbit) {
    MockEngine mock_engine;

    _kepler_orbit_rotated.relocate_on_orbit(
            (math::dec(49) /
             _kepler_orbit.get_orbit().get_orbit_properties().period) *
            math::Utilits::to_grad(math::const_2_pi));

    EXPECT_CALL(mock_engine, get_part_of_seconds_in_tick()).Times(1).WillOnce(
            testing::Return(1.f));
    _kepler_orbit_rotated.move(mock_engine);

    math::decimal_t period = _kepler_orbit_rotated.get_orbit()
            .get_orbit_properties().period;
    math::decimal_t a
            = _kepler_orbit_rotated.get_orbit()
                    .get_orbit_properties().variables.x;
    math::decimal_t b
            = _kepler_orbit_rotated.get_orbit()
                    .get_orbit_properties().variables.y;
    math::decimal_t ans_x
            = _kepler_orbit_rotated.get_orbit().get_orbit_properties().basis.x
              + 2 * a - a * (1 - std::sqrt(1 - (b * b) / (a * a)));
    EXPECT_TRUE(
            math::Utilits::is_equal(_kepler_orbit_rotated.get_pos().x, ans_x))
                        << "Is not equal x: "
                        << _kepler_orbit_rotated.get_pos().x << " and "
                        << ans_x;
    EXPECT_TRUE(math::Utilits::is_equal(_kepler_orbit_rotated.get_pos().y
                                        , _kepler_orbit_rotated.get_orbit()
                    .get_orbit_properties().basis.y))
                        << "Is not equal y: "
                        << _kepler_orbit_rotated.get_pos().y << " and "
                        << _kepler_orbit_rotated.get_orbit()
                                .get_orbit_properties().basis.y;

    EXPECT_CALL(mock_engine, get_part_of_seconds_in_tick()).Times(1).WillOnce(
            testing::Return((_down_kepler_pos / math::const_2_pi)
                            * period - period / math::dec(2)));
    _kepler_orbit_rotated.move(mock_engine);

    ans_x = ans_x - a;
    EXPECT_TRUE(
            math::Utilits::is_equal(_kepler_orbit_rotated.get_pos().x, ans_x))
                        << "Is not equal x: "
                        << _kepler_orbit_rotated.get_pos().x << " and "
                        << ans_x;
    EXPECT_TRUE(math::Utilits::is_equal(_kepler_orbit_rotated.get_pos().y,
            _kepler_orbit_rotated.get_orbit()
                    .get_orbit_properties().basis.y + b))
                        << "Is not equal y: "
                        << _kepler_orbit_rotated.get_pos().y << " and "
                        << _kepler_orbit_rotated.get_orbit()
                                   .get_orbit_properties().basis.y + b;
}

TEST_F(OrbitFixture, newton_test) {
    MockEngine mock_engine;

    EXPECT_CALL(mock_engine, get_cals_in_tick()).Times(1).WillOnce(
            testing::Return(10));
    EXPECT_CALL(mock_engine, calc_force_by_object(testing::Ref(_newton_orbit)))
            .Times(10)
            .WillRepeatedly(testing::Return(math::Vector2d(
                    math::coords_t(10, 5))));

    math::coords_t start_vel = _newton_orbit.get_velocity().get_coords();
    auto diff = math::Vector2d(math::coords_t(
            (start_vel.x * 2 + 10 + 100) * 10 / math::dec(2)
            , (start_vel.y * 2 + 5 + 50) * 10 / math::dec(2)));
    math::coords_t start = _newton_orbit.get_pos();

    _newton_orbit.move(mock_engine);

    EXPECT_TRUE(math::Utilits::is_equal(_newton_orbit.get_pos().x,
            start.x + diff.get_coords().x))
                        << "Is not equal x: "
                        << _newton_orbit.get_pos().x << " and "
                        << start.x + diff.get_coords().x;

    EXPECT_TRUE(math::Utilits::is_equal(_newton_orbit.get_pos().y,
            start.y + diff.get_coords().y))
                        << "Is not equal y: "
                        << _newton_orbit.get_pos().y << " and "
                        << start.y + diff.get_coords().y;
}
