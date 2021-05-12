#pragma once

#include <physics/interface.hpp>
#include <physics/physical_object.hpp>



namespace physics {

const math::decimal_t G = 6.674e-3f;
const math::decimal_t base_impulse = 25;
const math::decimal_t one_ton = 1e-4f;

class StoreObject;

class NewtonForce : public Force {
  public:
    NewtonForce();

    [[nodiscard]]
    math::Vector2d get_force(PhysicalObject &object
                            , const std::vector<
                                    std::reference_wrapper<PhysicalObject>
                                    > &other_objects) const override;

};

class OrbitalMechanic {
  public:
    OrbitalMechanic() = default;

    [[nodiscard]]
    math::decimal_t get_effective_radius_orbit(const Force &force
                                       , const PhysicalObject &object) const;
};

class Mechanic {
  public:
    Mechanic() = delete;

    explicit Mechanic(const Force &force);

    [[nodiscard]]
    math::decimal_t get_effective_circle_orbit
            (const PhysicalObject &object) const;

    [[nodiscard]]
    math::Vector2d calc_force_by_object(PhysicalObject &object
                                        , const StoreObject &objects) const;

  protected:
    const Force &_force;
    OrbitalMechanic _orbit_mechanic;
};


}  // namespace physics
