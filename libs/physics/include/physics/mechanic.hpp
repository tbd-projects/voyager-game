#pragma once

#include <physics/interface.hpp>
#include <physics/physical_object.hpp>

const double G = 6.67;
#define BASE_TRUST 25

namespace physics {

class StoreObject;

class NewtonForce : public Force {
  public:
    NewtonForce();

    [[nodiscard]]
    math::Vector2d get_force(PhysicalObject &object
                            , const std::vector<
                                    std::reference_wrapper<PhysicalObject>
                                    > &other_objects) const override;

  private:
    const math::decimal_t _G;
    const math::decimal_t _base_trust;
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

    explicit Mechanic(std::unique_ptr<Force> &&force);

    [[nodiscard]]
    math::decimal_t get_effective_circle_orbit
            (const PhysicalObject &object) const;

    [[nodiscard]]
    math::Vector2d calc_force_by_object(PhysicalObject &object
                                        , const StoreObject &objects) const;

  protected:
    std::unique_ptr<Force> _force;
    OrbitalMechanic _orbit_mechanic;
};


}  // namespace physics
