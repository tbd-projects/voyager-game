//
// Created by volodya on 15.04.2021.
//

#include "sf_texture_loader.h"

std::unique_ptr<graphics::ITexture> graphics::sf::SfTextureLoader::load(const std::string &filename) {
    ::sf::Texture sf_texture;
    if (!sf_texture.loadFromFile(filename))
        throw std::exception();

    auto texture = new SfTexture(std::move(sf_texture));

    return std::unique_ptr<SfTexture>(texture);
}
