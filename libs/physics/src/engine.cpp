#include <functional>

#include <debug/exception.hpp>

#include "special_object.hpp"
#include "physical_object.hpp"

#include "engine.hpp"

namespace physics {


//  ---------------------------------Engine------------------------------------


Engine::Engine()
        : _tick_of_calc(2)
          , _mechanic(NewtonForce()) {}

Engine::Engine(const Force &force)
        : _tick_of_calc(2)
          , _mechanic(force) {}

math::Vector2d Engine::calc_force_by_object(PhysicalObject &object) const {
    if (!_objects.contain_object(object)) {
        throw debug::PhysicalException("Working with an unregistered object");
    }

    return _mechanic.calc_force_by_object(object, _objects);
}

math::decimal_t Engine::get_effective_circle_orbit
        (const PhysicalObject &object) const {
    return _mechanic.get_effective_circle_orbit(object);
}

bool Engine::check_collision(const PhysicalObject &object) const {
    auto objects = _objects.get_active_object();

    return std::any_of(objects.begin(), objects.end(), [&object](
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

void Engine::add_object(std::weak_ptr<PhysicalObject> object) {
    _objects.add_object(std::move(object));
}

void Engine::delete_object(std::weak_ptr<PhysicalObject> object) {
    _objects.delete_object(std::move(object));
}

void StoreObject::add_object(std::weak_ptr<PhysicalObject> object) {
    if (object.lock()->_index != -1) {
        return;
    }

    if (_deleted_objects.empty()) {
        object.lock()->_index = (ssize_t) _objects.size();
        _objects.push_back(object);
    } else {
        object.lock()->_index = (ssize_t) *_deleted_objects.begin();
        _objects[*_deleted_objects.begin()] = object;
        _deleted_objects.erase(_deleted_objects.begin());
    }
}

std::vector<std::weak_ptr<PhysicalObject>>
StoreObject::get_active_object() const {
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

void StoreObject::delete_object(std::weak_ptr<PhysicalObject> object) {
    _deleted_objects.insert(object.lock()->_index);
    object.lock()->_index = -1;
}

bool StoreObject::contain_object(const PhysicalObject &object) const {
    ssize_t index = object._index;
    return index != -1 && _deleted_objects.find(index) == _deleted_objects.end()
           && (size_t)index < _objects.size();
}

bool StoreObject::is_objects_with_equal_id(const PhysicalObject &object_1
                                      , const PhysicalObject &object_2) const {
    return object_1._index == object_2._index;
}


}  // namespace physics
