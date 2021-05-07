//
// Created by volodya on 06.05.2021.
//

#include "sf/sf_graphics_factory.h"
#include <SFML/Graphics/Texture.hpp>
#include <sf/sf_rect.h>
#include "sf/sf_sprite.h"
#include "sf/sf_texture.h"
#include "sf/sf_font.h"
#include "sf/sf_text.h"
#include "sf/sf_canvas.h"
#include "texture_storage.h"

namespace graphics::sf {

    std::unique_ptr<ITexture> SfGraphicsFactory::create_texture(const std::string &filename) {
        ::sf::Texture sf_texture;
        if (!sf_texture.loadFromFile(filename))
            throw std::exception();

        auto texture = std::unique_ptr<ITexture>(new SfTexture(std::move(sf_texture)));

        return texture;
    }

    std::unique_ptr<Sprite> SfGraphicsFactory::create_sprite(const SpriteInfo &info, TextureStorage &storage) {
        auto texture = dynamic_cast<SfTexture *> (storage.get(info.filename));
        if (info.frames == 0) {
            return std::unique_ptr<Sprite>(new sf::SfSprite(info.pos, info.size, texture));
        }
        return std::unique_ptr<Sprite>(new sf::SfHorizontalAnimatedSprite(info.frames, info.pos, info.size, texture));
    }

    std::shared_ptr<Font> SfGraphicsFactory::create_font() {
        return std::make_shared<sf::SfFont>();
    }

    std::unique_ptr<Text> SfGraphicsFactory::create_text() {
        return std::make_unique<sf::SfText>();
    }

    std::unique_ptr<ICanvas> SfGraphicsFactory::create_canvas() {
        return std::make_unique<SfCanvas>();
    }

    std::unique_ptr<ICanvas> SfGraphicsFactory::create_canvas(int width, int height, bool is_full) {
        return std::unique_ptr<ICanvas>(new SfCanvas(width, height,is_full));
    }

    std::unique_ptr<Rect> SfGraphicsFactory::create_rect() {
        return std::make_unique<SfRect>();
    }

    Button SfGraphicsFactory::create_button() {
        return Button(create_rect().release(), create_text().release());
    }
}