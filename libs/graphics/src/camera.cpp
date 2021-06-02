// Владимир Ларин
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
    auto screen_pos = get_coords(pos);
    sprite.set_pos(screen_pos);
    sprite.scale(_size);

    double position_bounds[] = {
            -sprite.get_size().x * _size,
            1920 + sprite.get_size().x * _size,
            -sprite.get_size().y * _size,
            1080 + sprite.get_size().y * _size
    };

    sprite.set_visible(!(
            screen_pos.x < position_bounds[0] ||
            screen_pos.x > position_bounds[1] ||
            screen_pos.y < position_bounds[2] ||
            screen_pos.y > position_bounds[3]
            ));

}

const math::coords_t &graphics::Camera::get_center() const {
    return _center;
}

void graphics::Camera::set_center(const math::coords_t &center) {
    _center = center;
}

math::coords_t graphics::Camera::get_coords(const math::coords_t &pos) const {
    return (pos - _pos) * math::coords_t(_size, -_size) + _center;
}
