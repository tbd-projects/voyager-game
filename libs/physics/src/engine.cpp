#include <functional>

#include <debug/exception.hpp>

#include "math/interface.hpp"
#include "special_object.hpp"
#include "physical_object.hpp"
#include "game_manager/config.hpp"
#include "engine.hpp"


namespace physics {

#define MILISECOND_IN_SECOND 100.f


//  ---------------------------------Engine------------------------------------


Engine::Engine()
        : Engine(std::make_unique<NewtonForce>()) {}

Engine::Engine(std::unique_ptr<Force> &&force)
        : _cals_in_tick(20)
          , _part_of_second_in_tick(
                (math::decimal_t) game_manager::Config::get_instance().fps
                / MILISECOND_IN_SECOND)
          , _mechanic(std::move(force)) {}

math::Vector2d Engine::calc_force_by_object(PhysicalObject &object) const {
    if (!_objects.contain_object(object)) {
        throw debug::PhysicalException("Working with an unregistered object");
    }

    math::Vector2d ans = _mechanic.calc_force_by_object(object, _objects);
    if (object.have_some_impulse()) {
        ans += math::Vector2d(object.target_impulse(), base_impulse);
    }

    return ans * _part_of_second_in_tick;
}

math::decimal_t Engine::get_effective_circle_orbit
        (const PhysicalObject &object) const {
    return _mechanic.get_effective_circle_orbit(object);
}

bool Engine::check_collision(const PhysicalObject &object) const {
    auto objects = _objects.get_active_objects();

    return std::any_of(objects.begin(), objects.end(), [this, &object](
            const std::weak_ptr<PhysicalObject> &obj) {
        if (!obj.expired()) {
            auto gotten_object = obj.lock();
            if (!_objects.is_objects_with_equal_id(*gotten_object, object)) {
                math::decimal_t distance = math::Vector2d(
                        object.get_pos() - gotten_object->get_pos()).sqr_len();
                if (distance <= COLLIDE_DISTANCE * COLLIDE_DISTANCE) {
                    if (object.is_colides(*gotten_object)) {
                        return true;
                    }
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


size_t Engine::get_cals_in_tick() const {
    return _cals_in_tick;
}

math::decimal_t Engine::get_part_of_seconds_in_tick() const {
    return _part_of_second_in_tick;
}

math::decimal_t Engine::get_mass_fuel_by_one_impulse() const {
    return base_impulse / one_ton;
}

std::vector<math::coords_t> Engine::get_orbit_outline(
        const PhysicalObject &object) const {
    auto calc_force = [this](const PhysicalObject &object) -> math::Vector2d {
        math::Vector2d ans{};
        for (const auto &obj : _objects.get_active_objects()) {
            if (!obj.expired()) {
                auto gotten_object = obj.lock();
                if (!_objects.is_objects_with_equal_id(
                        *gotten_object, object)) {
                    ans += _mechanic.get_force()->get_force(object,
                                                            *gotten_object);
                }
            }
        }
        return ans;
    };

    math::coords_t pos = object.get_pos();
    PhysicalObject tmp_object(std::make_unique<math::CirclePolygon>(), pos, {},
                              object.get_weight());

    math::runge_func func_x = [&calc_force, &tmp_object]
            (const math::system_of_diff_equations &x,
             math::system_of_diff_equations &dx,
             math::decimal_t t) -> void {
        auto acelr = calc_force(tmp_object);

        dx.result_second_equation = acelr.get_coords().x;
        dx.result_first_equation = x.result_second_equation;
    };

    math::runge_func func_y = [&calc_force, &tmp_object]
            (const math::system_of_diff_equations &x,
             math::system_of_diff_equations &dx,
             math::decimal_t t) -> void {
        auto acelr = calc_force(tmp_object);

        dx.result_second_equation = acelr.get_coords().y;
        dx.result_first_equation = x.result_second_equation;
    };

    std::unique_ptr<math::IRungeKuttaMethod> solver_x
            = game_manager::Config::get_instance().creater_runge_kutta
                    (func_x, {pos.x, object.get_velocity().get_coords().x});

    std::unique_ptr<math::IRungeKuttaMethod> solver_y
            = game_manager::Config::get_instance().creater_runge_kutta
                    (func_y, {pos.y, object.get_velocity().get_coords().y});

    std::vector<math::coords_t> ans = {pos};

    math::decimal_t step = 20;
    math::decimal_t t = 0;
    math::coords_t start_pos = pos;
    math::decimal_t exepc_len = 0;

    while (math::Vector2d(pos, start_pos).sqr_len() > exepc_len) {
        pos.x = solver_x->do_step(math::decm(t), 20);
        pos.y = solver_y->do_step(math::decm(t), 20);
        tmp_object.set_pos(pos);
        ans.push_back(pos);

        if (t == step * 2) {
            exepc_len = math::Vector2d(pos, start_pos).sqr_len();
        }
    }

    return ans;
}


//  -----------------------------StoreObjects------------------------------------


void StoreObjects::add_object(std::weak_ptr<PhysicalObject> object) {
    if (object.expired()) {
        return;
    }

    auto gotten_object = object.lock();
    if (gotten_object->_index != -1) {
        return;
    }

    if (_deleted_objects.empty()) {
        gotten_object->_index = (ssize_t) _objects.size();
        _objects.push_back(object);
    } else {
        gotten_object->_index = (ssize_t) *_deleted_objects.begin();
        _objects[*_deleted_objects.begin()] = object;
        _deleted_objects.erase(_deleted_objects.begin());
    }
}

std::vector<std::weak_ptr<PhysicalObject>>
StoreObjects::get_active_objects() const {
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

void StoreObjects::delete_object(std::weak_ptr<PhysicalObject> object) {
    if (!object.expired()) {
        _deleted_objects.insert(object.lock()->_index);
        object.lock()->_index = -1;
    }
}

bool StoreObjects::contain_object(const PhysicalObject &object) const {
    ssize_t index = object._index;
    return index != -1 && _deleted_objects.find(index) == _deleted_objects.end()
           && (size_t) index < _objects.size();
}

bool StoreObjects::is_objects_with_equal_id(const PhysicalObject &first_object,
                                    const PhysicalObject &second_object) const {
    return first_object._index == second_object._index;
}


}  // namespace physics
