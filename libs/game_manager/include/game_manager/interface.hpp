#pragma once
#include <filesystem>

namespace game_manager {
class Config;

class ILoaderConfig {
  public:
    virtual void load(const std::filesystem::path& root
                      , Config &config) const = 0;
};

class GameManager;

namespace command {

class ICommand {
  public:
    virtual void execute(game_manager::GameManager &manager) = 0;

    virtual ~ICommand() = default;
};

}

}  // namespace game_manager
