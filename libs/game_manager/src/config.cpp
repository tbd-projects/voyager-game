#include "config.hpp"

namespace game_manager {

Config::Config()
        : player_id(0)
          , fps(60)
          , levels_path()
          , sprites_path()
          , stats_path()
          , properties_path()
          , graphics_factory(nullptr)
          , sprite_loader(nullptr)
          , properties_loader(nullptr)
          , progress_loader(nullptr)
          , levels_loader(nullptr)
          , creater_runge_kutta() {}

const Config &game_manager::Config::get_instance() {
    return _get_instance();
}

Config &Config::_get_instance() {
    static Config instance;

    return instance;
}

void
Config::load(const std::filesystem::path &root, const ILoaderConfig &loader) {
    auto &config = _get_instance();
    loader.load(root, config);
}

void Config::init(const IInitDependencies &initer) {
    auto &config = _get_instance();
    initer.init(config);
}

}  // namespace game_manager
