#include <game_manager/config.hpp>

#include <sf_graphics/sf_graphics_factory.h>
#include <graphics/json_sprite_sheet_loader.h>

#include "init_configs_loaders.hpp"

namespace game_manager::imported {

void InitLoadersForConfig::init(Config &config) const {
    config.graphics_factory
            = std::make_shared<graphics::sf::SfGraphicsFactory>();
    config.sprite_loader = std::make_shared<graphics::JsonSpriteSheetLoader>(
            *config.graphics_factory);
    config.properties_loader
            = std::make_shared<game::JsonPlayerPropertiesLoader>(
            config.properties_path);
    config.progress_loader = std::make_shared<game::BaseProgressLoader>(
            config.stats_path);
    config.levels_loader = std::make_shared<game::JsonCreateLevel>(
            config.levels_path);
    config.level_manager = std::make_shared<game::LevelManager>();
}

}  // namespace game_manager::imported
