// Владимир Ларин
// Created by volodya on 15.04.2021.
//

#include "sf_graphics/sf_texture.h"

int graphics::sf::SfTexture::get_height() {
    return static_cast<int>(_texture.getSize().y);
}

int graphics::sf::SfTexture::get_width() {
    return static_cast<int>(_texture.getSize().x);
}

graphics::sf::SfTexture::SfTexture(::sf::Texture &&texture) {
    _texture = texture;
}

::sf::Texture &graphics::sf::SfTexture::get_sf_texture() {
    return _texture;
}
