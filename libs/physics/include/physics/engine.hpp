#pragma once

#include <vector>
#include <set>
#include <memory>

#include <physics/interface.hpp>
#include <math.hpp>


namespace physics {

class Engine : private IConnectToEngine {
  public:
    Engine();

    math::decimal_t calc_force_by_object(size_t obj_index) const;

    math::decimal_t get_effective_circle_orbit
                                (const IInfluenceableByForce& object) const;

    math::decimal_t solve_kepler(math::decimal_t eccentricity
                                 , math::decimal_t mean_anomaly) const;

    void add_object(std::unique_ptr<IInfluenceableByForce> object) override;

    void delete_object(std::unique_ptr<IInfluenceableByForce> object) override;

  private:
    const math::decimal_t _G;
    const math::decimal_t _base_trust;
    const size_t _tick_of_calc;

    std::vector<std::reference_wrapper<IInfluenceableByForce>> _objects;
    std::set<size_t> _deleted_objects;

    math::decimal_t _base_solve_kepler(math::decimal_t eccentricity
                                       , math::decimal_t mean_anomaly) const;

    math::decimal_t _advance_solve_kepler(math::decimal_t eccentricity
                                          , math::decimal_t mean_anomaly) const;

    math::decimal_t _hyp_solve_kepler(math::decimal_t eccentricity
                                      , math::decimal_t mean_anomaly) const;

    friend class IInfluenceableByForce;
};

}  // namespace physics
