#include "astronomical_object.hpp"
#include <memory>
#include <iostream>
#include <cmath>

namespace physics {


//  -------------------------AstronomicalObject--------------------------------


AstronomicalObject::AstronomicalObject(std::unique_ptr<math::Polygon> &&polygon)
        : PhysicalObject(std::move(polygon))
          , _orbit() {}

AstronomicalObject::AstronomicalObject(std::unique_ptr<math::Polygon> &&polygon
                                       , size_t weight
                                       , math::Vector2d velocity
                                       , math::coords_t pos)
        : PhysicalObject(std::move(polygon), pos, velocity, weight)
          , _orbit() {}

AstronomicalObject::AstronomicalObject(std::unique_ptr<math::Polygon> &&polygon
                                       , size_t weight
                                       , math::Vector2d velocity
                                       , math::coords_t pos
                                       , Orbit::orbit_properties_t orbit)
        : PhysicalObject(std::move(polygon), pos, velocity, weight)
          , _orbit(orbit) {}

constexpr const Orbit &AstronomicalObject::get_orbit() const noexcept {
    return _orbit;
}

void AstronomicalObject::relocate_on_orbit(math::decimal_t angle) {
    _orbit.relocate_on_orbit(angle);
}

void AstronomicalObject::move(const Engine &physical_engine) {
    math::Vector2d last_velocity = get_velocity();
    _orbit.get_current_pos(*this, physical_engine);

  /*  math::decimal_t cos = last_velocity ^
                          get_velocity();

    math::decimal_t angle = math::Utilits::to_grad(
            std::acos(std::max(std::min(cos, 1.f), -1.f)));

    add_rotation(angle);*/
}

}  // namespace physics
