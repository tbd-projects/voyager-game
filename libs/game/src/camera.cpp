//
// Created by flashie on 13.05.2021.
//
#include "camera.hpp"


math::coords_t game::Camera::get_follow_position() {
    return this->_follow_pos;
}

void game::Camera::set_follow_position(math::coords_t follow_pos) {
    this->_follow_pos = follow_pos;
}

math::coords_t game::Camera::get_position(math::coords_t observe_pos) {
    return observe_pos - _ship->get_pos() + _follow_pos;;

}
