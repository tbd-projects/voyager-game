// Владимир Ларин
// Created by volodya on 24.05.2021.
//

#include <cmath>
#include <sf_graphics/sf_orbit_shape.h>
#include <sf_graphics/sf_window.h>


void graphics::sf::SfOrbitShape::draw(graphics::ICanvas *canvas) {
    auto &window = *dynamic_cast<game_manager::SfWindow *>(canvas);

    window.get_sf_window().draw(_shape);
}

void graphics::sf::SfOrbitShape::set_orbit(const physics::Orbit::orbit_properties_t &orbit) {
    OrbitShape::set_orbit(orbit);
//    auto pos = _shape.getPosition();
//    _shape = ::sf::ConvexShape();
//    SfOrbitShape::set_color(get_color());
//    _shape.setPosition(pos);

    auto axis = orbit.variables;
    auto rot = orbit.angle_target;

    if (!axis.x || !axis.y) return;

    size_t nums = std::min(100., 2 * M_PI * std::max(axis.x, axis.y) / 8);

    auto step = 2 * M_PI / nums;

    _shape.setPointCount(nums);

    math::decimal_t angle = 0;
    _shape.setRotation(0);
    for (size_t i = 0; i < nums; ++i)
    {
        angle += step;

        math::decimal_t x = axis.x * cos(angle);
        math::decimal_t y = axis.y * sin(angle);

        _shape.setPoint(i, ::sf::Vector2<float>(x, y));
    }

    auto fnc = [](math::coords_t basis, math::coords_t varibles) -> math::coords_t {
        if (varibles.x < varibles.y) {
            std::swap(varibles.x, varibles.y);
        }

        return basis + math::coords_t(std::sqrt(varibles.x * varibles.x - varibles.y * varibles.y), 0);
    };

    auto focus = fnc({0,0}, axis);

    _shape.setOrigin(focus.x, focus.y);

    _shape.setRotation(-rot);
}

void graphics::sf::SfOrbitShape::set_color(const Color &color) {
    OrbitShape::set_color(color);
    auto c = get_color();

    _shape.setOutlineThickness(5);
    _shape.setOutlineColor(::sf::Color(c.red, c.green, c.blue));
    _shape.setFillColor(::sf::Color(255,0,0, 0));
}

void graphics::sf::SfOrbitShape::set_pos(const math::coords_t &pos) {
    _shape.setPosition(pos.x, pos.y);
}

graphics::sf::SfOrbitShape::SfOrbitShape() {
    SfOrbitShape::set_color(get_color());
}

void graphics::sf::SfOrbitShape::scale(math::decimal_t scale) {
    _shape.setScale(scale, scale);
}

