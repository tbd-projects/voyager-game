//
// Created by volodya on 09.05.2021.
//

#ifndef VOYAGER_CONFIG_H
#define VOYAGER_CONFIG_H

#include <cstdlib>
#include <filesystem>
#include <graphics/i_graphics_factory.h>
#include <graphics/i_spite_loader.h>
//#include <loaders/properties_loader.hpp>
//#include <loaders/progress_loader.hpp>
//#include <loaders/level_loader.hpp>

namespace game_manager {
    class Config {
    public:
        std::size_t player_id = 1;
        std::size_t fps = 60;
        std::filesystem::path levels_path = "data/levels/example_level.json";
        std::filesystem::path sprites_path = "data/sprites.json";
        std::filesystem::path stats_path = "data/player/example_stats.json";
        std::filesystem::path properties_path = "data/player/example_properties.json";

        std::shared_ptr<graphics::IGraphicsFactory> graphics_factory;
        std::shared_ptr<graphics::ISpiteLoader> sprite_loader;
//        std::shared_ptr<PlayerPropertiesLoader> properties_loader;
//        std::shared_ptr<BaseProgressLoader> progress_loader;
//        std::shared_ptr<CreatorLevel> levels_loader;

    protected:
        Config();
    public:
        Config(Config &other) = delete;
        void operator=(const Config &) = delete;
        static const Config& get_instance();
    };
}

#endif //VOYAGER_CONFIG_H
