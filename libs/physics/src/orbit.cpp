//
// Модуль Ветошкина Артёма
//

#define _USE_MATH_DEFINES

#include <cmath>

#include "orbit.hpp"

namespace physics {


//  ---------------------------------Orbit-------------------------------------


Orbit::orbit_properties_t::orbit_properties_t(math::coords_t variables
                                              , math::coords_t basis
                                              , math::decimal_t angle_target
                                              , math::decimal_t period)
        : variables(variables)
          , basis(basis)
          , angle_target(angle_target)
          , period(period) {}

Orbit::Orbit(PhysicalObject &object, Orbit::orbit_properties_t orbit_properties)
        : _major_axis(orbit_properties.variables.x)
          , _small_axis(orbit_properties.variables.y)
          , _eccentricity(0)
          , _lgitude_of_periapsis(orbit_properties.angle_target
                                  + math::Utilits::to_grad(math::dec(M_PI)
                                                           + math::dec(M_PI_2)))
          , _period(orbit_properties.period)
          , _current_epoch_time(0)
          , _basis(orbit_properties.basis)
          , _use_kepler(true) {
    math::decimal_t a = orbit_properties.variables.x;
    math::decimal_t b = orbit_properties.variables.y;

    if (b > a) {
        std::swap(a, b);
    }

    _eccentricity = std::sqrt((a * a - b * b) / (a * a));

    _set_pos_on_kepler_orbit(object);
}

Orbit::Orbit()
        : _major_axis()
          , _small_axis()
          , _eccentricity()
          , _lgitude_of_periapsis()
          , _period()
          , _current_epoch_time()
          , _basis()
          , _use_kepler(false) {}

math::coords_t Orbit::get_current_pos(PhysicalObject &object
                                      , const Engine &physical_engine) {
    if (_use_kepler) {
        _kepler_move(object, std::move(physical_engine));
    } else {
        _newtom_move(object, std::move(physical_engine));
    }
    return object.get_pos();
}

Orbit::orbit_properties_t Orbit::get_orbit_properties() const {
    return {math::coords_t(_major_axis, _small_axis), _basis,
            _lgitude_of_periapsis, _period};
}

void Orbit::relocate_on_orbit(math::decimal_t angle) {
    _current_epoch_time = (math::Utilits::to_rad(angle) / math::const_2_pi)
                          * _period;
}

void Orbit::_kepler_move(PhysicalObject &object
                         , const Engine &physical_engine) {
    _current_epoch_time += physical_engine.get_part_of_seconds_in_tick();
    _current_epoch_time
            -= _period < _current_epoch_time ? _period : math::dec(0);
    _set_pos_on_kepler_orbit(object);
}

void Orbit::_set_pos_on_kepler_orbit(PhysicalObject &object) const {
    auto rounding_angle = [](math::decimal_t &angle) -> void {
        while (std::abs(angle) > math::const_2_pi) {
            angle -= angle < 0 ? -math::const_2_pi : math::const_2_pi;
        }
    };

    math::decimal_t M = (math::const_2_pi / _period) * _current_epoch_time;

    math::EquationKepler equation(_eccentricity, M);
    math::decimal_t E = equation.solve();

    rounding_angle(E);

    math::decimal_t cos_E = std::cos(E);
    math::decimal_t x = _major_axis * (cos_E - _eccentricity);

    math::decimal_t y = std::sqrt(_major_axis * _major_axis *
                                  (1 - _eccentricity * _eccentricity) *
                                  (1 - cos_E * cos_E));
    y *= std::sin(E) > 0 ? 1 : -1;

    math::coords_t new_pos(x, y);

    math::GeometryFunction geometry;
    new_pos = geometry.rotate_point(new_pos, _lgitude_of_periapsis, {0, 0});
    new_pos += _basis;
    object.set_pos(new_pos);
}

void Orbit::_newtom_move(PhysicalObject &object
                         , const Engine &physical_engine) {
    size_t times_calc = physical_engine.get_cals_in_tick();
    for (size_t i = 0; i < times_calc; ++i) {
        auto acceleration = physical_engine.calc_force_by_object(object);
        object.set_velocity(object.get_velocity() + acceleration);
        object.set_pos(object.get_pos() + object.get_velocity().get_coords());
    }
    object.complete_add_impulse();
}


}  // namespace physics
