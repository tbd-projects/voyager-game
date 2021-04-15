#include "astronimical_object.hpp"
#include <memory>
#include <iostream>

namespace physics {


//  -------------------------AstronomicalObject--------------------------------


AstronomicalObject::AstronomicalObject(size_t weight
                                       , math::Vector2d velocity
                                       , math::coords_t pos
                                       , std::unique_ptr<Engine>&&
                                               physical_engine)
        : IInfluenceableByForce(std::move(physical_engine))
          , _orbit()
          , _velocity(velocity)
          , _pos(pos)
          , _weight(weight)
          , _target_add_trust(0)
          , _need_add_trust(false) {}

AstronomicalObject::AstronomicalObject(size_t weight
                                       , math::Vector2d velocity
                                       , math::coords_t pos
                                       , Orbit::orbit_properties_t orbit
                                       , std::unique_ptr<Engine>&&
                                               physical_engine)
        : IInfluenceableByForce(std::move(physical_engine))
          , _orbit(orbit)
          ,  _velocity(velocity)
          , _pos(pos)
          , _weight(weight)
          , _target_add_trust(0)
          , _need_add_trust(false) {}

void AstronomicalObject::add_rotation_trust(math::decimal_t target) {
    _need_add_trust = true;
    _target_add_trust = target;
}

const Orbit &AstronomicalObject::get_orbit() {
    return _orbit;
}

void AstronomicalObject::move_on_orbit(math::decimal_t angle) {
    _orbit.move_by_angle(angle);
}

void AstronomicalObject::move(const Engine& physical_engine) {
}

size_t AstronomicalObject::get_weight() const {
    return _weight;
}

math::coords_t AstronomicalObject::get_position() const {
    return _pos;
}

math::Vector2d &AstronomicalObject::get_velocity() {
    return _velocity;
}

bool AstronomicalObject::have_some_trust() const {
    return _need_add_trust;
}

math::decimal_t AstronomicalObject::target_trust() const {
    return _target_add_trust;
}

void AstronomicalObject::free_current_trust() {
    _target_add_trust = 0;
    _need_add_trust = false;
}

}  // namespace physics
