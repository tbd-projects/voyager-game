//
// Модуль Ветошкина Артёма
//

#include "special_object.hpp"
#include "math/polygon.hpp"

namespace physics {


//  --------------------------IndexedPhysicalObject-----------------------------


EnginesIndexedObject::EnginesIndexedObject()
        : _index(-1) {}


//  ------------------------AcceleratableObject---------------------------------


AcceleratableObject::AcceleratableObject()
        : _need_impulse(false)
          , _target_impulse(0) {}

bool AcceleratableObject::have_some_impulse() const noexcept {
    return _need_impulse;
}

math::decimal_t AcceleratableObject::target_impulse() const noexcept {
    return _target_impulse;
}

void AcceleratableObject::add_impulse(math::decimal_t target) {
    _need_impulse = true;
    _target_impulse = target;
}

void AcceleratableObject::complete_add_impulse() {
    _need_impulse = false;
    _target_impulse = 0;
}

ColideObject::ColideObject(std::unique_ptr<math::Polygon> &&polygon)
        : _polygon(std::move(polygon)) {}

bool ColideObject::is_colide(const ColideObject &object) const {
    return _polygon->intresect(*object._polygon) ||
           object._polygon->intresect(*_polygon);
}

math::coords_t ColideObject::get_pos() const noexcept {
    return _polygon->get_pos();
}

void ColideObject::set_pos(math::coords_t pos) {
    _polygon->set_pos(pos);
}

std::unique_ptr<math::Polygon> &ColideObject::get_polygon() {
    return _polygon;
}

math::decimal_t ColideObject::get_rotation() const noexcept {
    return _polygon->get_rotation();
}

void ColideObject::add_rotation(math::decimal_t offset_angle) {
    _polygon->add_rotation(offset_angle);
}

void ColideObject::set_rotation(math::decimal_t angle) {
    _polygon->set_rotation(angle);
}

const std::unique_ptr<math::Polygon> &ColideObject::get_polygon() const {
    return _polygon;
}

}  // namespace physics
