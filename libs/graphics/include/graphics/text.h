// Владимир Ларин
// Created by volodya on 15.04.2021.
//

#ifndef VOYAGER_I_TEXT_H
#define VOYAGER_I_TEXT_H

#include <string>
#include <filesystem>
#include "font.h"
#include "i_drawable.h"
#include "math/polygon.hpp"

namespace graphics {
    class Text : public IDrawable, public math::PositionateObject {
    private:
        int _size = 16;
        Color _color = Color(0, 0, 0);
    public:
        Text() = default;

        virtual int get_size() const;

        virtual void set_size(int size);

        virtual Color get_color() const;

        virtual void set_color(const Color &color);
    private:
        std::string _string;
        std::shared_ptr<Font> _font;
    public:
        virtual Font &get_font();

        virtual void set_font(std::shared_ptr<Font> font);

        virtual const std::string &get_string();

        virtual void set_string(const std::string &string);

        virtual int get_width() = 0;

        ~Text() override = default;
    };
}


#endif //VOYAGER_I_TEXT_H
