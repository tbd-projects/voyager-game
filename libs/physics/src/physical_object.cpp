#include "physical_object.hpp"

namespace physics {


//  -----------------------------PhysicalObject--------------------------------


PhysicalObject::PhysicalObject(std::unique_ptr<math::Polygon> &&polygon)
        : ColideObject(std::move(polygon))
          , _weight(0)
          , _velocity(math::Vector2d(0, 0)) {}

PhysicalObject::PhysicalObject(std::unique_ptr<math::Polygon> &&polygon
                               , math::coords_t pos
                               , math::Vector2d velocity, size_t weight)
        : ColideObject(std::move(polygon))
          , _weight(weight)
          , _velocity(velocity) {
    set_pos(pos);
}

size_t PhysicalObject::get_weight() const noexcept {
    return _weight;
}

constexpr const math::Vector2d &PhysicalObject::get_velocity() const noexcept {
    return _velocity;
}

void PhysicalObject::set_velocity(math::Vector2d velocity) {
    _velocity = velocity;
}

void PhysicalObject::set_weight(size_t weight) {
    _weight = weight;
}

}  // namespace physics
