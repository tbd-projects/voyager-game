#include "mechanic.hpp"
#include "physical_object.hpp"
#include "engine.hpp"

namespace physics {


//  --------------------------------NewtonForce---------------------------------


NewtonForce::NewtonForce() {}

math::Vector2d NewtonForce::get_force(PhysicalObject &object
                                      , const std::vector<std::reference_wrapper<PhysicalObject>>
&other_objects) const {
    math::Vector2d ans{};
    for (auto other_object : other_objects) {
        math::Vector2d r = math::Vector2d(object.get_pos() - object.get_pos());
        math::decimal_t force =
                (G * other_object.get().get_cast_weight()) / r.sqr_len();
        ans += force * r.normalize();
    }

    if (object.have_some_impulse()) {
        ans += math::Vector2d(base_impulse, object.target_impulse());
        object.complete_add_impulse();
    }

    return ans;
}


//  ---------------------------OrbitalMechanic----------------------------------


math::decimal_t OrbitalMechanic::get_effective_radius_orbit
        (const Force &force, const PhysicalObject &object) const {
    auto object_weight_one_ton
            = PhysicalObject(std::make_unique<math::CirclePolygon>());


    math::decimal_t force_to_one_ton = force(PhysicalObject(&tmp))
    return 0;
}


//  ------------------------------Mechanic--------------------------------------


Mechanic::Mechanic(const Force &force)
        : _force(force) {}

math::decimal_t Mechanic::get_effective_circle_orbit(
        const PhysicalObject &object) const {
    return _orbit_mechanic.get_effective_radius_orbit(_force, object);
}

math::Vector2d Mechanic::calc_force_by_object(PhysicalObject &object
                                              , const StoreObject &objects) const {
    std::vector<std::reference_wrapper<PhysicalObject>> other_object;

    auto tmp = objects.get_active_object();

    for (const auto &obj : tmp) {
        if (objects.is_objects_with_equal_id(*obj.lock(), object)) {
            other_object.push_back(*obj.lock());
        }
    }

    return _force.get_force(object, other_object);
}


}  // namespace physics
