#include "orbit.hpp"

namespace physics {


//  ---------------------------------Orbit-------------------------------------


Orbit::orbit_properties_t::orbit_properties_t()
        : variables()
          , pos()
          , is_ellipse(true) {}

Orbit::Orbit(Orbit::orbit_properties_t orbit_properties) {}

math::coords_t Orbit::get_current_pos(PhysicalObject &object
                                      , const Engine &physical_engine) {
    auto acceleration = physical_engine.calc_force_by_object(object);
    return object.get_pos() + acceleration.get_coords();
}

Orbit::orbit_properties_t Orbit::get_orbit_properties() const {
    return Orbit::orbit_properties_t();
}

void Orbit::relocate_on_orbit(math::decimal_t angle) {
}

}  // namespace physics
