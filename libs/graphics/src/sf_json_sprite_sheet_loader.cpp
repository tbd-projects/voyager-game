//
// Created by volodya on 15.04.2021.
//

#include "graphics/sf_json_sprite_sheet_loader.h"
#include "graphics/sf_sprite.h"



std::unique_ptr<graphics::ISprite> graphics::sf::SfJsonSpriteSheetLoader::load(int id, TextureStorage &storage) {
    SfTexture *texture = dynamic_cast<SfTexture *>(storage.get(""));

    auto sprite = new SfHorizontalAnimatedSprite(0, SfSprite(std::pair<int, int>(0,0), std::pair<int, int>(0,0), *texture));

    return std::unique_ptr<SfHorizontalAnimatedSprite>(sprite);
}
