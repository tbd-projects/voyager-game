#include "orbit.hpp"

namespace physics {


//  ---------------------------------Orbit-------------------------------------


Orbit::Orbit(Orbit::orbit_properties_t orbit_properties) {
}

math::coords_t Orbit::get_current_pos(IInfluenceableByForce &object
                                      , const Engine &physical_engine) {
    return math::coords_t();
}

Orbit::orbit_properties_t Orbit::get_orbit_properties() const {
    return Orbit::orbit_properties_t();
}

void Orbit::move_by_angle(math::decimal_t angle) {
}

Orbit::orbit_properties_t::orbit_properties_t()
    : variables()
    , pos()
    , is_ellipse(true) {}

}  // namespace physics
