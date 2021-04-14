#pragma once

#include <unistd.h>

#include <umath.h>

namespace physics {

class Engine;

class IMovable {
  public:
    virtual void move(Engine &physical_engine) = 0;
};

class Collision;

class ICollisionable {
  public:
    virtual bool check_collision(const Collision &collision) = 0;
};


class IInfluenceableByForce {
  public:
    IInfluenceableByForce()
            : _index(-1) {}

    virtual math::coords_t get_position() = 0;

    virtual math::Vector2d &get_velocity() = 0;

    virtual bool have_some_trust() = 0;

    virtual math::decimal_t target_trust() = 0;

    virtual void free_current_trust() = 0;

    virtual size_t get_weight() = 0;

  private:
    friend class Engine;

    ssize_t _index;
};

class IConnectToEngine {
  public:
    virtual void add_object(IInfluenceableByForce& object) = 0;

    virtual void delete_object(IInfluenceableByForce& object) = 0;
};
}