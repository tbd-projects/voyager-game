#include <functional>

#include "engine.h"

namespace physics {

#define G 6.67
#define BASE_TRUST 25

//---------------------------------Engine--------------------------------------

Engine::Engine()
    : _G(G)
    , _base_trust(BASE_TRUST)
    , _tick_of_calc(2)
    , _objects()
    , _deleted_objects() {}

math::decimal_t Engine::calc_force_by_object(size_t obj_index) {
    return 0;
}

math::decimal_t Engine::get_effective_circle_orbit(const IInfluenceableByForce &object) {
    return 0;
}

math::decimal_t Engine::solve_kepler(math::decimal_t eccentricity, math::decimal_t mean_anomaly) {
    return 0;
}

void Engine::add_object(IInfluenceableByForce &object) {
    if (_deleted_objects.empty()) {
        object._index = _objects.size();
        _objects.push_back(std::ref(object));
    } else {
        object._index = *_deleted_objects.begin();
        _objects[*_deleted_objects.begin()] = std::ref(object);
        _deleted_objects.erase(_deleted_objects.begin());
    }
}

void Engine::delete_object(IInfluenceableByForce &object) {
    _deleted_objects.insert(object._index);
}

math::decimal_t Engine::_base_solve_kepler(math::decimal_t eccentricity, math::decimal_t mean_anomaly) {
    return 0;
}

math::decimal_t Engine::_advance_solve_kepler(math::decimal_t eccentricity, math::decimal_t mean_anomaly) {
    return 0;
}

math::decimal_t Engine::_hyp_solve_kepler(math::decimal_t eccentricity, math::decimal_t mean_anomaly) {
    return 0;
}

}