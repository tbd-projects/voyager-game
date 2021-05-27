// Владимир Ларин
// Created by volodya on 06.05.2021.
//
#include "graphics/text.h"
namespace graphics {

    Font &Text::get_font() {
        return *_font;
    }

    void Text::set_font(std::shared_ptr<Font> font) {
        _font = std::move(font);
    }

    const std::string &Text::get_string() {
        return _string;
    }

    void Text::set_string(const std::string &string) {
        _string = string;
    }

    int Text::get_size() const{
        return _size;
    }

    void Text::set_size(int size) {
        if (size < 0)
            throw;

        _size = size;
    }

    Color Text::get_color() const{
        return _color;
    }

    void Text::set_color(const Color &color) {
        _color = color;
    }
}
