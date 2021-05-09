//
// Created by volodya on 09.05.2021.
//
#include "config.h"

#include <graphics/sf/sf_graphics_factory.h>
#include <graphics/json_sprite_sheet_loader.h>

namespace game_manager {
    const Config& game_manager::Config::get_instance() {
        static Config instance;

        return instance;
    }

    Config::Config() {
        auto root_dir = std::filesystem::path(__FILE__).parent_path() / "../../../";
        graphics_factory = std::make_shared<graphics::sf::SfGraphicsFactory>();
        sprite_loader = std::make_shared<graphics::JsonSpriteSheetLoader>(*graphics_factory);
        properties_loader = std::make_shared<JsonPlayerPropertiesLoader>(properties_path);
        progress_loader = std::make_shared<BaseProgressLoader>(stats_path);
        levels_loader = std::make_shared<JsonCreateLevel>(levels_path);
    }
}