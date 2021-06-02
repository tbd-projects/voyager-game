#include "mechanic.hpp"
#include "physical_object.hpp"
#include "engine.hpp"

namespace physics {


//  --------------------------------NewtonForce---------------------------------


NewtonForce::NewtonForce() {}

math::Vector2d NewtonForce::get_force(const PhysicalObject &object,
                                  const PhysicalObject &other_object) const {
    math::Vector2d r = math::Vector2d(other_object.get_pos()
                                      - object.get_pos());
    math::decimal_t force =
            (G * other_object.get_cast_weight())
            / (r.sqr_len() * one_dist);

    return force * r.normalize();
}


//  ---------------------------OrbitalMechanic----------------------------------


math::decimal_t OrbitalMechanic::get_effective_radius_orbit
        (const Force &force, const PhysicalObject &object) const {
    math::decimal_t object_dimensions = object.get_polygon()
            ->get_bounders_rect().get_circumscribed_circ();
    PhysicalObject tmp(std::make_unique<math::CirclePolygon>()
                       , object.get_pos() + object_dimensions, {}, 1);

    math::decimal_t force_to_one_ton = force.get_force(tmp, object).sqr_len();

    return object_dimensions + EFFECTIVE_DIFF_ORBIT *
                               (1 + std::abs(std::log10(force_to_one_ton)) / 10);
}


//  ------------------------------Mechanic--------------------------------------


Mechanic::Mechanic(std::unique_ptr<Force> &&force)
        : _force(std::move(force)) {}

math::decimal_t Mechanic::get_effective_circle_orbit(
        const PhysicalObject &object) const {
    return _orbit_mechanic.get_effective_radius_orbit(*_force, object);
}

math::Vector2d Mechanic::calc_force_by_object(const PhysicalObject &object,
                                          const StoreObjects &objects) const {
    std::vector<std::reference_wrapper<const PhysicalObject>> other_object;

    auto tmp = objects.get_active_objects();

    math::Vector2d ans{};
    math::decimal_t object_dimensions = object.get_polygon()
            ->get_bounders_rect().get_circumscribed_circ_sqr();

    math::Vector2d normal_velocity = object.get_velocity().normalize();

    for (const auto &obj : tmp) {
        if (!obj.expired()) {
            auto current_object = obj.lock();
            if (!objects.is_objects_with_equal_id(*current_object, object)) {
                ans += _force->get_force(object, *current_object);

                if (!current_object->have_effective_orbit()) {
                    continue;
                }

                math::decimal_t effective_orbit
                        = get_effective_circle_orbit(*current_object);

                effective_orbit *= effective_orbit;

                math::decimal_t upper_bounder =
                        effective_orbit + object_dimensions;
                math::decimal_t lower_bounder =
                        effective_orbit - object_dimensions;

                math::decimal_t distance
                        = math::Vector2d(current_object->get_pos(),
                                         object.get_pos()).sqr_len();
                if (upper_bounder >= distance && lower_bounder <= distance) {
                    ans += normal_velocity * math::decm(0.0006);
                }
            }
        }
    }

    return ans;
}

const std::unique_ptr<Force> &Mechanic::get_force() const {
    return _force;
}


}  // namespace physics
