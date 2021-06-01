#include <gtest/gtest.h>

#include <vector>
#include <deque>

#include <physics.hpp>

class EngineFixture : public testing::Test {
  public:
    EngineFixture() {
        _objects.emplace_back(std::make_shared<physics::PhysicalObject>(
                std::make_unique<math::CirclePolygon>(math::CirclePolygon(
                        math::coords_t(0, 0), 5.65685))
                , math::coords_t(0, 0), math::Vector2d(25, 0), 32));

        _objects.emplace_back(std::make_shared<physics::PhysicalObject>(
                std::make_unique<math::RectanglePolygon>(math::RectanglePolygon(
                        math::coords_t(7.58342, 4.99844), 7, 6.40985))
                , math::coords_t(7.58342, 4.99844), math::Vector2d(50, 2), 32));

        _objects.emplace_back(std::make_shared<physics::PhysicalObject>(
                std::make_unique<math::TrianglePolygon>(math::TrianglePolygon(
                        math::coords_t(2.33347, 6.92783), 8, 5.664899))
                , math::coords_t(2.33347, 6.92783), math::Vector2d(40, -30)
                , 32));

        _engine.add_object(_objects[0]);

        _engine.add_object(_objects[1]);

        _engine.add_object(_objects[2]);
    }

    ~EngineFixture() override {
        _engine.delete_object(_objects[0]);

        _engine.delete_object(_objects[1]);

        _engine.delete_object(_objects[2]);
    }

  protected:
    physics::Engine _engine;

    std::vector<std::shared_ptr<physics::PhysicalObject>> _objects;
};

TEST_F(EngineFixture, ColideFunction) {
    EXPECT_TRUE(_engine.check_collision(*_objects[0]));
    EXPECT_TRUE(_engine.check_collision(*_objects[1]));
    EXPECT_TRUE(_engine.check_collision(*_objects[2]));
    _objects[0]->get_polygon()->scale(0.1);
    EXPECT_FALSE(_engine.check_collision(*_objects[0]));
}
