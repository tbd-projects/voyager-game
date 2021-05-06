//
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
}