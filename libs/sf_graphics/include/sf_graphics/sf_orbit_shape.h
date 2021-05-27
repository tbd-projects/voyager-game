// Владимир Ларин
// Created by volodya on 24.05.2021.
//

#ifndef VOYAGER_SF_ORBIT_SHAPE_H
#define VOYAGER_SF_ORBIT_SHAPE_H

#include <graphics/orbit_shape.h>
#include <SFML/Graphics/ConvexShape.hpp>

namespace graphics::sf {

    class SfOrbitShape: public OrbitShape {
    private:
        ::sf::ConvexShape _shape;
    public:
        SfOrbitShape();

        void draw(ICanvas *canvas) override;

        ~SfOrbitShape() override = default;

        void set_color(const Color &color) override;

        void set_pos(const math::coords_t &pos) override;

        void set_orbit(const physics::Orbit::orbit_properties_t &orbit) override;

        void scale(math::decimal_t scale) override;
    };
}

#endif //VOYAGER_SF_ORBIT_SHAPE_H
