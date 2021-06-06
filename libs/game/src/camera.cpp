// Дмитрий Варин
//
// Created by flashie on 13.05.2021.
//
#include "camera.hpp"


void game::Camera::update() {
    set_pos(_ship->get_pos());
    set_size((1 - std::min(_ship->get_velocity().len() / 4, 0.3)) / 1.7);
    // set_size(0.2);
}

