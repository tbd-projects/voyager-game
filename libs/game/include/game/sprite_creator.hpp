#pragma once

#include <memory>
#include "interface.hpp"
//#include "graphics/sf/sf_texture.h"

namespace graphics {
    class sf {
    public:
        class SfGraphicsFactory {

        };
    };
}
namespace game {
    class MapSpriteCreator {
    public:
        MapSpriteCreator() = delete;

        MapSpriteCreator(const MapSpriteCreator &) = delete;

        MapSpriteCreator &operator=(const MapSpriteCreator &) = delete;

        MapSpriteCreator(graphics::sf::SfGraphicsFactory &factory) {
            this->_texture_storage = factory;
        };

        std::unique_ptr<Sprite> get_sprite(size_t id);

    private:
        graphics::sf::SfGraphicsFactory _texture_storage;
    };
} // namespace game