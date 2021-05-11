#include "orbit.hpp"

namespace physics {


//  ---------------------------------Orbit-------------------------------------


Orbit::orbit_properties_t::orbit_properties_t()
        : variables()
          , pos() {}

Orbit::Orbit(Orbit::orbit_properties_t orbit_properties)
        : _major_axis(orbit_properties.variables.x)
          , _eccentricity(0)
          , _inclination(0)
          , _lgitude_ascend_node(0)
          , _lgitude_of_periapsis(orbit_properties.angle_target)
          , _mean_lgitude()
          , _pos(orbit_properties.pos)
          , _use_kepler(true) {
    math::decimal_t a = orbit_properties.variables.x;
    math::decimal_t b = orbit_properties.variables.y;

    if (b > a) {
        std::swap(a, b);
    }

    _eccentricity = (a * a - b * b) / (a * a);
}

Orbit::Orbit()
        : _major_axis()
          , _eccentricity()
          , _inclination()
          , _lgitude_ascend_node()
          , _lgitude_of_periapsis()
          , _mean_lgitude()
          , _use_kepler(false) {}

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
