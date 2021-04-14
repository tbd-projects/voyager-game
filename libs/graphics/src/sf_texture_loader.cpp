//
// Created by volodya on 15.04.2021.
//

#include "sf_texture_loader.h"

std::unique_ptr<graphics::ITexture> graphics::sf::SfTextureLoader::load(const std::string &filename) {

    auto texture = new SfTexture(::sf::Texture());
    return std::unique_ptr<SfTexture>(texture);
}
