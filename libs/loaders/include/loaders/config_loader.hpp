#pragma once

#include <game_manager/config.hpp>

namespace game_manager::imported {

class ConfigJsonLoader : public game_manager::ILoaderConfig {
  public:
    ConfigJsonLoader() = default;

    void load(const std::filesystem::path& root, Config& config) const override;
};

}  // namespace game_manager::imported
