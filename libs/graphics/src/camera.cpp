//
// Created by volodya on 26.05.2021.
//

#include "camera.h"

const math::coords_t &graphics::Camera::get_pos() const {
    return _pos;
}

void graphics::Camera::set_pos(const math::coords_t &pos) {
    _pos = pos;
}

const math::decimal_t &graphics::Camera::get_size() const {
    return _size;
}

void graphics::Camera::set_size(const math::decimal_t &size) {
    _size = size;
}

void graphics::Camera::apply(Sprite &sprite, const math::coords_t &pos) const {

    sprite.set_pos((pos - _pos) * math::coords_t(_size, -_size) + _center);
    sprite.scale(_size);
}

const math::coords_t &graphics::Camera::get_center() const {
    return _center;
}

void graphics::Camera::set_center(const math::coords_t &center) {
    _center = center;
}
