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
        math::coords_t pos;
        math::decimal_t angle_target;

        orbit_properties_t();
    };

    Orbit();

    explicit Orbit(orbit_properties_t orbit_properties);

    math::coords_t get_current_pos(PhysicalObject &object
                                   , const Engine &physical_engine);

    [[nodiscard]]
    orbit_properties_t get_orbit_properties() const;

    void relocate_on_orbit(math::decimal_t angle);

  private:
    math::decimal_t _major_axis;
    math::decimal_t _eccentricity;
    math::decimal_t _inclination;
    math::decimal_t _lgitude_ascend_node;
    math::decimal_t _lgitude_of_periapsis;
    math::decimal_t _mean_lgitude;
    math::coords_t _pos;
    bool _use_kepler;
};

}  // namespace physics
