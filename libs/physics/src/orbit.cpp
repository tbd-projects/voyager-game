#include "orbit_tests.h"

namespace physics {


//---------------------------------Orbit---------------------------------------


Orbit::Orbit(Engine &physical_engine) {

}

Orbit::Orbit(Orbit::orbit_properties_t orbit_properties) {

}

math::coords_t Orbit::get_current_pos(IInfluenceableByForce &object
                                      , Engine &physical_engine) {
    return math::coords_t();
}

Orbit::orbit_properties_t Orbit::get_orbit_properties() {
    return Orbit::orbit_properties_t();
}

void Orbit::move_by_angle(math::decimal_t angle) {

}

}