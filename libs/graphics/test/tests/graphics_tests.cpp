 
#include <gtest/gtest.h>
#include "graphics/graphics.h"
#include "graphics/sf_texture_loader.h"

TEST (GraphicsTextureStorage, Get) {
    graphics::sf::SfTextureLoader loader;

    graphics::TextureStorage storage(&loader);

    graphics::sf::SfTexture *texture = dynamic_cast<graphics::sf::SfTexture *>(storage.get("texture.png"));


    ASSERT_EQ(texture->get_height(), 200);
    ASSERT_EQ(texture->get_width(), 200);
}

