#include "mechanic.hpp"
#include "physical_object.hpp"

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
        (const Mechanic &base_mechanic, const PhysicalObject &object) const {
    return 0;
}


//  ------------------------------Mechanic--------------------------------------


Mechanic::Mechanic(const Force &force)
        : _force(force) {}


}  // namespace physics
