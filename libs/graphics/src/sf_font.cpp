//
// Created by volodya on 06.05.2021.
//

#include "sf/sf_font.h"

void graphics::sf::SfFont::set_path(const std::filesystem::path &path) {
    Font::set_path(path);
    if (!_font.loadFromFile(path.string()))
        throw std::exception();
}

const ::sf::Font& graphics::sf::SfFont::get_sf_font() const{
    return _font;
}

