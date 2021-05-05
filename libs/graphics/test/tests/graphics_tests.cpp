
#include <gtest/gtest.h>
#include "graphics/graphics.h"
#include "graphics/sf_texture_loader.h"
#include "graphics/sf_json_sprite_sheet_loader.h"
#include "graphics/sf_canvas.h"
#include <cmath>

TEST (GraphicsTextureStorage, Get) {
    graphics::sf::SfTextureLoader loader;

    graphics::TextureStorage storage(&loader);

    graphics::sf::SfTexture *texture = dynamic_cast<graphics::sf::SfTexture *>(storage.get(
            "./libs/graphics/test/tests/sprites_info/1.png"));


    ASSERT_EQ(texture->get_height(), 100);
    ASSERT_EQ(texture->get_width(), 100);
}


TEST (GraphicsTextureStorage, GetSprite) {
    graphics::sf::SfTextureLoader loader;

    graphics::TextureStorage storage(&loader);

    graphics::sf::SfJsonSpriteSheetLoader sheet_loader;

    auto sprite = sheet_loader.load(0, storage);
    graphics::SfCanvas canvas;

    for (double i = 0; i <= 5000; ++i) {
        double x = i / 10.;
        double y = x * (1 + sin(x / 100));
        canvas.clear();
        sprite->draw(&canvas);
        sprite->set_pos(std::pair(x, y));
        canvas.apply();
    }
}

TEST (GraphicsTextureStorage, SpriteAnimation) {
    graphics::sf::SfTextureLoader loader;

    graphics::TextureStorage storage(&loader);

    graphics::sf::SfJsonSpriteSheetLoader sheet_loader;

    auto sprite = dynamic_cast<graphics::AnimatedSprite *>(sheet_loader.load(1, storage).release());
    graphics::SfCanvas canvas;

    for (int i = 0; i <= 5000; ++i) {
        double x = i / 100.;
        canvas.clear();
        sprite->draw(&canvas);
        if (i % 50 == 0) sprite->next_frame();
        sprite->set_pos(std::pair(x, 100));
        canvas.apply();
    }
}

