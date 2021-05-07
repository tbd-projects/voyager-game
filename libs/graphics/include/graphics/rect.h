//
// Created by volodya on 07.05.2021.
//

#ifndef VOYAGER_RECT_H
#define VOYAGER_RECT_H

#include "i_drawable.h"
#include "math/polygon.hpp"
#include "color.h"

namespace graphics {

class Rect: public IDrawable, public math::RectanglePolygon {
private:
    Color _fill_color = Color(0,0,0, 0);
    Color _border_color;
    int _border_width = 0;
public:
    [[nodiscard]] const Color &get_fill_color() const;

    void set_fill_color(const Color &fill_color);

    [[nodiscard]] const Color &get_border_color() const;

    void set_border_color(const Color &border_color);

    [[nodiscard]] int get_border_width() const;

    void set_border_width(int border_width);
};
}

#endif //VOYAGER_RECT_H
