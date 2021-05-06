#pragma once

#include <physics/interface.hpp>
#include <physics/physical_object.hpp>

#define G 6.67
#define BASE_TRUST 25

namespace physics {

class NewtonForce : public Force {
  public:
    NewtonForce();

    [[nodiscard]]
    math::Vector2d get_force(PhysicalObject &object
          , const std::vector<std::reference_wrapper<PhysicalObject>>
          &other_objects) const override;

  private:
    const math::decimal_t _G;
    const math::decimal_t _base_trust;
};

class Mechanic {
  public:
    Mechanic() = delete;

    explicit Mechanic(const Force& force);

    virtual ~Mechanic() = default;

  protected:
    const Force& _force;
};

class OrbitalMechanic {
  public:
    OrbitalMechanic() = default;

    math::decimal_t get_effective_radius_orbit(const Mechanic& base_mechanic
                                       , const PhysicalObject& object) const;
};

}  // namespace physics
