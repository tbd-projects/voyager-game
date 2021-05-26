//
// Created by volodya on 24.05.2021.
//

#ifndef VOYAGER_ORBIT_SHAPE_H
#define VOYAGER_ORBIT_SHAPE_H

#include <physics/orbit.hpp>
#include "i_drawable.h"
#include "color.h"

namespace graphics {
class OrbitShape: public IDrawable, public math::IScalable {
        physics::Orbit::orbit_properties_t _orbit;
        Color _color = Color(255,255,255);
    public:
        [[nodiscard]] const physics::Orbit::orbit_properties_t &get_orbit() const;

        virtual void set_orbit(const physics::Orbit::orbit_properties_t &orbit);

        virtual void set_pos(const math::coords_t &pos) = 0;

        [[nodiscard]] const Color &get_color() const;

        virtual void set_color(const Color &color);

        ~OrbitShape() override = default;
    };
}

#endif //VOYAGER_ORBIT_SHAPE_H
