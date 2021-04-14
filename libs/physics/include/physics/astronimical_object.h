#pragma once

#include <physics/interface.h>
#include <physics/engine.h>
#include <physics/orbit_tests.h>
#include <umath.h>

namespace physics {

class AstronomicalObject : public IMovable, public IInfluenceableByForce {
  public:
    AstronomicalObject() = delete;

    AstronomicalObject(size_t weight
            , math::Vector2d velocity
            , math::coords_t pos
            , Engine& physical_engine);

    explicit AstronomicalObject(size_t weight
                       , math::Vector2d velocity
                       , math::coords_t pos
                       , Orbit::orbit_properties_t orbit
                       , IConnectToEngine& physical_engine);

    AstronomicalObject(const AstronomicalObject& object) = delete;

    AstronomicalObject& operator=(const AstronomicalObject& object) = delete;

    void add_rotation_trust(math::decimal_t target);

    const Orbit& get_orbit();

    void move_on_orbit(math::decimal_t angle);

    void move(Engine &physical_engine) final;

    size_t get_weight() final;

    math::coords_t get_position() final;

    math::Vector2d &get_velocity() final;

    bool have_some_trust() final;

    math::decimal_t target_trust() final;

    void free_current_trust() final;

    ~AstronomicalObject();

  private:
    Orbit _orbit;
    math::Vector2d _velocity;
    math::coords_t _pos;
    size_t _weight;
    math::decimal_t _target_add_trust;
    IConnectToEngine& _engine;
    bool _need_add_trust;
};

}