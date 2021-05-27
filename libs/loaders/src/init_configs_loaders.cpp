//
// Модуль Ветошкина Артёма
//

#include <game_manager/config.hpp>

#include <sf_graphics/sf_graphics_factory.h>
#include <graphics/json_sprite_sheet_loader.h>

#include "loaders.hpp"

namespace game_manager::external {

void InitLoadersForConfig::init(Config &config) const {
    config.graphics_factory
            = std::make_shared<graphics::sf::SfGraphicsFactory>();
    config.sprite_loader = std::make_shared<graphics::JsonSpriteSheetLoader>(
            *config.graphics_factory);
    config.properties_loader
            = std::make_shared<game::external::JsonPlayerPropertiesLoader>(
            config.properties_path);
    config.progress_loader = std::make_shared<game::external::BaseProgressLoader>(
            config.stats_path);
    config.levels_loader = std::make_shared<game::external::JsonCreateLevel>(
            config.levels_path);

}

}  // namespace game_manager::imported
