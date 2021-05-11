#include "sprite_creator.hpp"

namespace game {
    std::unique_ptr<Sprite> MapSpriteCreator::get_sprite(size_t id) {
        // from config
        //graphics::JsonSpriteSheetLoader sheet_loader(loader);
        //std::unique_ptr<Sprite> sprite = sheet_loader.load(id, this->_texture_storage);
        //return sprite;

        return std::unique_ptr<Sprite>();
    }
} // namespace game

