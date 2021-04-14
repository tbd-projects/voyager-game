#include "astronimical_object.h"

namespace physics {


//-------------------------AstronomicalObject----------------------------------


AstronomicalObject::AstronomicalObject(size_t weight
                                       , math::Vector2d velocity
                                       , math::coords_t pos
                                       , Engine &physical_engine)
        : _orbit(physical_engine)
          , _velocity(velocity)
          , _pos(pos)
          , _weight(weight)
          , _target_add_trust(0)
          , _engine(reinterpret_cast<IConnectToEngine &>(physical_engine))
          , _need_add_trust(false) {
    _engine.add_object(static_cast<IInfluenceableByForce &>(*this));
}

AstronomicalObject::AstronomicalObject(size_t weight
                                       , math::Vector2d velocity
                                       , math::coords_t pos
                                       , Orbit::orbit_properties_t orbit
                                       , IConnectToEngine &physical_engine)
        : _orbit(orbit)
          ,  _velocity(velocity)
          , _pos(pos)
          , _weight(weight)
          , _target_add_trust(0)
          , _engine(reinterpret_cast<IConnectToEngine &>(physical_engine))
          , _need_add_trust(false) {
    _engine.add_object(static_cast<IInfluenceableByForce &>(*this));
}

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

AstronomicalObject::~AstronomicalObject() {
    _engine.delete_object(static_cast<IInfluenceableByForce &>(*this));
}

void AstronomicalObject::move(Engine &physical_engine) {

}

size_t AstronomicalObject::get_weight() {
    return _weight;
}

math::coords_t AstronomicalObject::get_position() {
    return _pos;
}

math::Vector2d &AstronomicalObject::get_velocity() {
    return _velocity;
}

bool AstronomicalObject::have_some_trust() {
    return _need_add_trust;
}

math::decimal_t AstronomicalObject::target_trust() {
    return _target_add_trust;
}

void AstronomicalObject::free_current_trust() {
    _target_add_trust = 0;
    _need_add_trust = false;
}

}