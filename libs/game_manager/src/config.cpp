#include "config.hpp"

#include <utility>

#include <sf_graphics/sf_graphics_factory.h>
#include <graphics/json_sprite_sheet_loader.h>

namespace game_manager {

Config::Config()
        : player_id(0)
          , fps(60)
          , levels_path("data/levels/example_level.json")
          , sprites_path("data/sprites.json")
          , stats_path("data/player/example_stats.json")
          , properties_path("data/player/example_properties.json")
          , graphics_factory(nullptr)
          , sprite_loader(nullptr)
          , properties_loader(nullptr)
          , progress_loader(nullptr)
          , levels_loader(nullptr)
          , level_manager(nullptr){}

const Config &game_manager::Config::get_instance() {
    return _get_instance();
}

Config &Config::_get_instance() {
    static Config instance;

    return instance;
}

void Config::load(const std::filesystem::path &root
                  , const ILoaderConfig &loader) {
    auto &config = _get_instance();
    loader.load(root, config);

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

}  // namespace game_manager
