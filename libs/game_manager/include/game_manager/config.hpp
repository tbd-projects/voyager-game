#pragma once

#include <graphics/i_graphics_factory.h>
#include <graphics/i_spite_loader.h>

#include <cstdlib>
#include <filesystem>

#include <game_manager/interface.hpp>
#include <game/interface.hpp>
#include <math/interface.hpp>

namespace game_manager {

class ILoaderConfig;

class Config {
  public:
    Config(Config &other) = delete;

    void operator=(const Config &) = delete;

    static const Config &get_instance();

    static void load(const std::filesystem::path &root,
                     const ILoaderConfig &loader);

    static void init(const IInitDependencies &initer);

    std::size_t player_id;
    std::size_t fps;
    std::string levels_path;
    std::string sprites_path;
    std::string stats_path;
    std::string properties_path;

    std::unique_ptr<graphics::IGraphicsFactory> graphics_factory;
    std::unique_ptr<graphics::ISpiteLoader> sprite_loader;
    std::unique_ptr<game::PlayerPropertiesLoader> properties_loader;
    std::unique_ptr<game::ProgressLoader> progress_loader;
    std::unique_ptr<game::CreatorLevel> levels_loader;

    std::function<std::unique_ptr<math::IRungeKuttaMethod>
            (math::runge_func,
             math::system_of_diff_equations)> creater_runge_kutta;

  protected:
    Config();

  private:
    static Config &_get_instance();
};

}  // namespace game_manager
