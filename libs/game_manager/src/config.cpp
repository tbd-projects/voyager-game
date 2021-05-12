#include "config.hpp"

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
          , levels_loader(nullptr) {}

const Config &game_manager::Config::get_instance() {
    return _get_instance();
}

Config &Config::_get_instance() {
    static Config instance;

    return instance;
}

void Config::load(const std::filesystem::path &root
                  , const ILoaderConfig &loader
                  , const IInitImportImplForConfig& initer) {
    auto &config = _get_instance();
    loader.load(root, config);
    initer.init(config);
}

}  // namespace game_manager
