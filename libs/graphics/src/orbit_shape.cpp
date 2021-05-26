//
// Created by volodya on 24.05.2021.
//

#include "orbit_shape.h"

const Color &graphics::OrbitShape::get_color() const {
    return _color;
}

void graphics::OrbitShape::set_color(const Color &color) {
    _color = color;
}

const physics::Orbit::orbit_properties_t &graphics::OrbitShape::get_orbit() const {
    return _orbit;
}

void graphics::OrbitShape::set_orbit(const physics::Orbit::orbit_properties_t &orbit) {
    _orbit = orbit;
}
