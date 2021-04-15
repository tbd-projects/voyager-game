#pragma once

#include <memory>
#include <physics/interface.hpp>
#include <physics/engine.hpp>
#include <physics/orbit.hpp>
#include <math.hpp>

namespace physics {

class AstronomicalObject : public IMovable, public IInfluenceableByForce {
  public:
    AstronomicalObject() = delete;

    AstronomicalObject(size_t weight
            , math::Vector2d velocity
            , math::coords_t pos
            , std::unique_ptr<Engine>&& physical_engine);

    explicit AstronomicalObject(size_t weight
                       , math::Vector2d velocity
                       , math::coords_t pos
                       , Orbit::orbit_properties_t orbit
                       , std::unique_ptr<Engine>&& physical_engine);

    AstronomicalObject(const AstronomicalObject& object) = delete;

    AstronomicalObject& operator=(const AstronomicalObject& object) = delete;

    void add_rotation_trust(math::decimal_t target);

    const Orbit& get_orbit();

    void move_on_orbit(math::decimal_t angle);

    void move(const Engine &physical_engine) final;

    size_t get_weight() const final;

    math::coords_t get_position() const final;

    math::Vector2d &get_velocity() final;

    bool have_some_trust() const final;

    math::decimal_t target_trust() const final;

    void free_current_trust() final;

    ~AstronomicalObject() override = default;

  private:
    Orbit _orbit;
    math::Vector2d _velocity;
    math::coords_t _pos;
    size_t _weight;
    math::decimal_t _target_add_trust;
    bool _need_add_trust;
};

}  // namespace physics
