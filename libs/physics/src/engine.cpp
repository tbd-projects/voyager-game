#include <functional>

#include <debug/exception.hpp>

#include "special_object.hpp"
#include "physical_object.hpp"

#include "engine.hpp"

namespace physics {


//  ---------------------------------Engine------------------------------------


Engine::Engine()
    : Mechanic(NewtonForce())
    , _tick_of_calc(2)
    , _orbital_mechanic() {}

Engine::Engine(const Force &force)
    : Mechanic(force)
    , _tick_of_calc(2)
    , _orbital_mechanic() {}

math::Vector2d Engine::calc_force_by_object(PhysicalObject &object) const {
    if (object._index == -1) {
        throw debug::PhysicalException("Working with an unregistered object");
    }

    if (_deleted_objects.find(object._index) != _deleted_objects.end()) {
        throw debug::PhysicalException("Working with deleted from engine "
                                       "object");
    }

    std::vector<std::reference_wrapper<PhysicalObject>> other_object;

    auto tmp = get_active_object();

    for (const auto& obj : tmp) {
        if (obj.lock()->_index != object._index) {
            other_object.push_back(*obj.lock());
        }
    }

    return _force.get_force(object, other_object);
}

math::decimal_t Engine::solve_kepler(math::decimal_t eccentricity
                                     , math::decimal_t mean_anomaly) const {
    return 0;
}

math::decimal_t Engine::_base_solve_kepler
                        (math::decimal_t eccentricity
                         , math::decimal_t mean_anomaly) const {
    return 0;
}

math::decimal_t Engine::_advance_solve_kepler
                        (math::decimal_t eccentricity
                        , math::decimal_t mean_anomaly) const {
    return 0;
}

math::decimal_t Engine::_hyp_solve_kepler
                        (math::decimal_t eccentricity
                        , math::decimal_t mean_anomaly) const {
    return 0;
}

math::decimal_t Engine::get_effective_circle_orbit
                                (const PhysicalObject &object) const {
    return _orbital_mechanic.get_effective_radius_orbit(*this, object);
}

bool Engine::check_collision(const PhysicalObject &object) const {
    auto objects = get_active_object();

    return std::any_of(_objects.begin(), _objects.end(), [&object](
            const std::weak_ptr<PhysicalObject> &obj) {
        if (obj.lock()->_index != object._index) {
            math::decimal_t distance = math::Vector2d(
                    object.get_pos() - obj.lock()->get_pos()).sqr_len();
            if (distance <= COLLIDE_DISTANCE * COLLIDE_DISTANCE) {
                if (object.is_colide(*obj.lock())) {
                    return true;
                }
            }
        }
        return false;
    });
}

void EngineStoreObject::add_object(std::weak_ptr<PhysicalObject> object) {
    if (object.lock()->_index != -1) {
        return;
    }

    if (_deleted_objects.empty()) {
        object.lock()->_index = (ssize_t)_objects.size();
        _objects.push_back(object);
    } else {
        object.lock()->_index = (ssize_t)*_deleted_objects.begin();
        _objects[*_deleted_objects.begin()] = object;
        _deleted_objects.erase(_deleted_objects.begin());
    }
}

std::vector<std::weak_ptr<PhysicalObject>>
                            EngineStoreObject::get_active_object()  const {
    std::vector<std::weak_ptr<PhysicalObject>> out;
    for (const auto &current_object : _objects) {
        if (current_object.expired()) {
            throw debug::PhysicalException("Found physical object, which was "
                                           "deleted in program without deleting"
                                           " from the engine");
        }

        if (_deleted_objects.find(current_object.lock()->_index) ==
            _deleted_objects.end()) {
            out.push_back(current_object);
        }
    }
    return out;
}

void EngineStoreObject::delete_object(std::weak_ptr<PhysicalObject> object) {
    _deleted_objects.insert(object.lock()->_index);
    object.lock()->_index = -1;
}


}  // namespace physics
