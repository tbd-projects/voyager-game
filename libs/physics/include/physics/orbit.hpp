#pragma once

#include <math.hpp>
#include <physics/engine.hpp>
#include <physics/interface.hpp>
#include <physics/physical_object.hpp>


namespace physics {


class Orbit {
  public:
    struct orbit_properties_t {
        math::coords_t variables;
        math::coords_t basis;
        math::decimal_t angle_target;
        math::decimal_t period;

        orbit_properties_t(math::coords_t variables = {},
                           math::coords_t basis = {},
                           math::decimal_t angle_target = {},
                           math::decimal_t period = {});
    };

    Orbit();

    explicit Orbit(PhysicalObject &object, orbit_properties_t orbit_properties);

    math::coords_t
    get_current_pos(PhysicalObject &object, const Engine &physical_engine);

    [[nodiscard]]
    orbit_properties_t get_orbit_properties() const;

    void relocate_on_orbit(math::decimal_t angle);

  private:
    math::decimal_t _major_axis;
    math::decimal_t _small_axis;
    math::decimal_t _eccentricity;
    math::decimal_t _lgitude_of_periapsis;
    math::decimal_t _period;
    math::decimal_t _current_epoch_time;
    math::coords_t _basis;
    bool _use_kepler;

    void _kepler_move(PhysicalObject &object, const Engine &physical_engine);

    void _set_pos_on_kepler_orbit(PhysicalObject &object) const;

    void _newton_move(PhysicalObject &object, const Engine &physical_engine);
};

}  // namespace physics
