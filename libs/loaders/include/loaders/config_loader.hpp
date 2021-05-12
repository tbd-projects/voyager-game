#pragma once

#include <game_manager/config.hpp>

namespace game_manager::imported {

class JsonLoader : public game_manager::ILoaderConfig {
  public:
    JsonLoader() = default;

    void load(const std::filesystem::path& root, Config& config) const override;
};

}  // namespace game_manager::imported
