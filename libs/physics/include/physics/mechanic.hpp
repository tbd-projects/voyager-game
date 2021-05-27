//
// Модуль Ветошкина Артёма
//

#pragma once

#include <physics/interface.hpp>
#include <physics/physical_object.hpp>

#define EFFECTIVE_DIFF_ORBIT 30

namespace physics {

const math::decimal_t G = 6.674e-3f;
const math::decimal_t base_impulse = 0.5e-3f;
const math::decimal_t one_ton = 1e-4f;
const math::decimal_t one_dist = 1e-2f;

class StoreObject;

class NewtonForce : public Force {
  public:
    NewtonForce();

    [[nodiscard]]
    math::Vector2d get_force(const PhysicalObject &object
                        , const PhysicalObject &other_objects) const override;
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
    math::Vector2d calc_force_by_object(const PhysicalObject &object
                                        , const StoreObject &objects) const;

    [[nodiscard]]
    const std::unique_ptr<Force>& get_force() const;

  protected:
    std::unique_ptr<Force> _force;
    OrbitalMechanic _orbit_mechanic;
};


}  // namespace physics
