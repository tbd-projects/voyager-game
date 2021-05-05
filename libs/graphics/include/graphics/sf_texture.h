//
// Created by volodya on 15.04.2021.
//

#ifndef VOYAGER_SF_TEXTURE_H
#define VOYAGER_SF_TEXTURE_H

#include "graphics/i_texture.h"
#include <SFML/Graphics.hpp>

namespace graphics::sf {
    class SfTexture : public ITexture {
    public:
        explicit SfTexture(::sf::Texture &&_texture);

        int get_height() override;

        int get_width() override;

        ::sf::Texture &get_sf_texture();

    private:
        ::sf::Texture _texture;
    };
}


#endif //VOYAGER_SF_TEXTURE_H
