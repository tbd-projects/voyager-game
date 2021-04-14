#pragma once

#include <physics/interface.h>
#include <umath.h>

namespace physics {

class Collision: public ICollisionable {
  public:
    Collision() = default;
    explicit Collision(math::coords_t pos, math::decimal_t angle);

    math::coords_t get_pos();

    void set_pos(math::coords_t pos);

    void set_rotation(math::decimal_t angle);

    void add_rotation(math::decimal_t offset_angle);

    math::decimal_t get_rotation() const;

    virtual void scale(math::decimal_t scale) = 0;

    virtual bool is_in_collision(math::coords_t point) const = 0;

    bool check_collision(const Collision &collision) override = 0;
  private:
    math::coords_t _pos;
    math::decimal_t _angle;
};

class RestangleCollision: public Collision {
  public:
    RestangleCollision() = default;

    RestangleCollision(math::coords_t pos, math::decimal_t height
                       , math::decimal_t width, math::decimal_t angle = 0);

    void resize(math::decimal_t height, math::decimal_t width);

    void scale(math::decimal_t scale) override;

    bool is_in_collision(math::coords_t point) const override;

    bool check_collision(const Collision &collision) override;

  private:
    math::decimal_t _height;
    math::decimal_t _width;
};

class TriangleCollision: public Collision {
  public:
    TriangleCollision() = default;

    TriangleCollision(math::coords_t pos, math::decimal_t height
                       , math::decimal_t width, math::decimal_t angle = 0);

    void resize(math::decimal_t height, math::decimal_t width);

    void scale(math::decimal_t scale) override;

    bool is_in_collision(math::coords_t point) const override;

    bool check_collision(const Collision &collision) override;

  private:
    math::decimal_t _height;
    math::decimal_t _width;
};

class CircleCollision: public Collision {
  public:
    CircleCollision() = default;

    CircleCollision(math::coords_t pos, math::decimal_t radius
                    , math::decimal_t angle = 0);

    void resize(math::decimal_t radius);

    void scale(math::decimal_t scale) override;

    bool is_in_collision(math::coords_t point) const override;

    bool check_collision(const Collision &collision) override;

  private:
    math::decimal_t _radius;
};

}