//
// Created by volodya on 26.05.2021.
//

#ifndef VOYAGER_CAMERA_H
#define VOYAGER_CAMERA_H


#include <math/utilits.hpp>
#include "sprite.h"

namespace graphics {
    class Camera {
    private:
        math::coords_t _pos = {0 ,0};
        math::coords_t _center = {0 ,0};
        math::decimal_t _size = 1;


    public:
        [[nodiscard]] const math::coords_t &get_pos() const;

        void set_pos(const math::coords_t &pos);

        [[nodiscard]] const math::coords_t &get_center() const;

        void set_center(const math::coords_t &center);

        [[nodiscard]] const math::decimal_t &get_size() const;

        void set_size(const math::decimal_t &size);

        void apply(Sprite &sprite, const math::coords_t &pos) const;

        math::coords_t get_coords(const math::coords_t &pos) const;
    };
}

#endif //VOYAGER_CAMERA_H
