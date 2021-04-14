#pragma once

#include <physics/interface.h>
#include <umath.h>
#include <vector>
#include <set>

namespace physics {

class Engine : private IConnectToEngine {
  public:
    Engine();

    math::decimal_t calc_force_by_object(size_t obj_index);

    math::decimal_t get_effective_circle_orbit(const IInfluenceableByForce& object);

    math::decimal_t solve_kepler(math::decimal_t eccentricity, math::decimal_t mean_anomaly);

    void add_object(IInfluenceableByForce &object) override;

    void delete_object(IInfluenceableByForce &object) override;

  private:
    math::decimal_t _G;
    math::decimal_t _base_trust;
    size_t _tick_of_calc;

    std::vector<std::reference_wrapper<IInfluenceableByForce>> _objects;
    std::set<size_t> _deleted_objects;

    math::decimal_t _base_solve_kepler(math::decimal_t eccentricity,  math::decimal_t mean_anomaly);

    math::decimal_t _advance_solve_kepler(math::decimal_t eccentricity, math::decimal_t mean_anomaly);

    math::decimal_t _hyp_solve_kepler(math::decimal_t eccentricity, math::decimal_t mean_anomaly);
};

}