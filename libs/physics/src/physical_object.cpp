#include "physical_object.hpp"
#include "mechanic.hpp"

namespace physics {


//  -----------------------------PhysicalObject--------------------------------


PhysicalObject::PhysicalObject(std::unique_ptr<math::Polygon> &&polygon)
        : ColideObject(std::move(polygon))
          , _weight(1)
          , _velocity(math::Vector2d(0, 0)) {}

PhysicalObject::PhysicalObject(std::unique_ptr<math::Polygon> &&polygon,
                               math::coords_t pos, math::Vector2d velocity,
                               size_t weight, bool have_effective_orbit)
        : ColideObject(std::move(polygon))
          , _weight(weight)
          , _velocity(velocity)
          , _have_effective_orbit(have_effective_orbit) {
    set_pos(pos);
}

size_t PhysicalObject::get_weight() const noexcept {
    return _weight;
}

math::decimal_t PhysicalObject::get_cast_weight() const noexcept {
    return math::decimal_t(_weight) * one_ton;
}

const math::Vector2d &PhysicalObject::get_velocity() const noexcept {
    return _velocity;
}

void PhysicalObject::set_velocity(math::Vector2d velocity) {
    _velocity = velocity;
}

void PhysicalObject::set_weight(size_t weight) {
    _weight = weight;
}

bool PhysicalObject::have_effective_orbit() const {
    return _have_effective_orbit;
}

}  // namespace physics
