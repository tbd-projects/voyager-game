#pragma once

#include <vector>
#include <set>
#include <memory>

#include <physics/interface.hpp>
#include <physics/mechanic.hpp>
#include <math.hpp>

namespace physics {

#define COLLIDE_DISTANCE 100

class PhysicalObject;
class EnginesIndexedObject;

class EngineStoreObject: public IConnectToEngine {
  public:
    EngineStoreObject() = default;

    void add_object(std::weak_ptr<PhysicalObject> object) override;

    void delete_object(std::weak_ptr<PhysicalObject> object) override;

  protected:
    std::vector<std::weak_ptr<PhysicalObject>> _objects;

    std::set<size_t> _deleted_objects;

    [[nodiscard]]
    std::vector<std::weak_ptr<PhysicalObject>> get_active_object() const;
};

class Engine : public EngineStoreObject, public Mechanic {
  public:
    Engine();

    explicit Engine(const Force& force);

    [[nodiscard]]
    math::Vector2d calc_force_by_object(PhysicalObject &object) const;

    [[nodiscard]]
    math::decimal_t get_effective_circle_orbit
                                (const PhysicalObject& object) const;

    [[nodiscard]]
    math::decimal_t solve_kepler(math::decimal_t eccentricity
                                 , math::decimal_t mean_anomaly) const;

    [[nodiscard]]
    bool check_collision(const PhysicalObject& object) const;

  private:
    const size_t _tick_of_calc;
    OrbitalMechanic _orbital_mechanic;

    math::decimal_t _base_solve_kepler(math::decimal_t eccentricity
                                       , math::decimal_t mean_anomaly) const;

    math::decimal_t _advance_solve_kepler(math::decimal_t eccentricity
                                          , math::decimal_t mean_anomaly) const;

    math::decimal_t _hyp_solve_kepler(math::decimal_t eccentricity
                                      , math::decimal_t mean_anomaly) const;
};

}  // namespace physics
