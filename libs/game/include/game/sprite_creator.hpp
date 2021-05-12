#pragma once

#include <memory>
#include "interface.hpp"
//#include <graphics/i_graphics_factory.h>
//#include <graphics/texture_storage.h>



namespace game {

    class MapSpriteCreator {
    public:
        MapSpriteCreator() = delete;

        MapSpriteCreator(const MapSpriteCreator &) = delete;

        MapSpriteCreator &operator=(const MapSpriteCreator &) = delete;

        explicit MapSpriteCreator(graphics::IGraphicsFactory &factory) : _texture_storage(factory) {

        };

        std::unique_ptr<graphics::Sprite> get_sprite(size_t id);

    private:
        graphics::TextureStorage _texture_storage;
    };
} // namespace game