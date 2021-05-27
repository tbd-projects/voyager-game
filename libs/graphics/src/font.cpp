// Владимир Ларин
// Created by volodya on 06.05.2021.
//

#include "graphics/font.h"

std::filesystem::path graphics::Font::get_path() const{
    return _path;
}

void graphics::Font::set_path(const std::filesystem::path &path) {
    _path = path;
}

graphics::Font::Font(const std::string &path) : _path(path) {

}

graphics::Font::Font(const std::filesystem::path &path) : _path(path) {

}
