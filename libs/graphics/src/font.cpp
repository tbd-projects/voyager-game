//
// Created by volodya on 06.05.2021.
//

#include "graphics/font.h"

std::filesystem::path graphics::Font::get_path() const{
    return _path;
}

void graphics::Font::set_path(const std::filesystem::path &path) {
    _path = path;
}

int graphics::Font::get_size() const{
    return _size;
}

void graphics::Font::set_size(int size) {
    _size = size;
}

Color graphics::Font::get_color() const{
    return _color;
}

void graphics::Font::set_color(const Color &color) {
    _color = color;
}

graphics::Font::Font(const std::string &path) : _path(path) {

}

graphics::Font::Font(const std::filesystem::path &path) : _path(path) {

}
