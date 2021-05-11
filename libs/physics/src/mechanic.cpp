#include "mechanic.hpp"
#include "physical_object.hpp"
#include "engine.hpp"

namespace physics {


//  --------------------------------NewtonForce---------------------------------


NewtonForce::NewtonForce()
        : _G(G)
      , _base_trust(BASE_TRUST) {}

math::Vector2d NewtonForce::get_force(PhysicalObject &object
               , const std::vector<std::reference_wrapper<PhysicalObject>>
                                &other_objects) const {
    math::Vector2d ans{};
    for (auto other_object : other_objects) {
        math::Vector2d r = math::Vector2d(object.get_pos()-object.get_pos());
        math::decimal_t force = (_G * math::decimal_t(object.get_weight()
                                * other_object.get().get_weight()))/r.sqr_len();
        ans += force * r.normalize();
    }

    if (object.have_some_trust()) {
        ans += math::Vector2d(_base_trust, object.target_trust());
        object.complete_add_trust();
    }

    return ans;
}


//  ---------------------------OrbitalMechanic----------------------------------


math::decimal_t OrbitalMechanic::get_effective_radius_orbit
        (const Force& force, const PhysicalObject &object) const {
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

    for (const auto& obj : tmp) {
        if (objects.is_objects_with_equal_id(*obj.lock(), object)) {
            other_object.push_back(*obj.lock());
        }
    }

    return _force.get_force(object, other_object);
}


}  // namespace physics
