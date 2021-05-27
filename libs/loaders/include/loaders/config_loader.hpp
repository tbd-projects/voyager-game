#pragma once

#include <game_manager/config.hpp>

namespace game_manager::external {

class ConfigJsonLoader : public game_manager::ILoaderConfig {
  public:
    ConfigJsonLoader() = default;

  private:
    void load(const std::filesystem::path& root, Config& config) const override;
};

}  // namespace game_manager::external
