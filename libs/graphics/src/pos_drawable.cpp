//
// Created by volodya on 06.05.2021.
//

#include <utility>
#include "graphics/sprite.h"
#include "pos_drawable.h"

std::pair<double, double> graphics::PosDrawable::get_pos() {
    return _pos;
}

void graphics::PosDrawable::set_pos(const std::pair<double, double> &pos) {
    _pos = pos;
}