#pragma once
#include <filesystem>
#include <event_controller/i_command.h>

namespace game_manager {
class Config;

class ILoaderConfig {
  public:
    virtual void load(const std::filesystem::path& root
                      , Config &config) const = 0;
};

class GameManager;

namespace command {

class ICommand: public event_controller::ICommand {
  public:
    void execute(game_manager::GameManager &manager) override = 0;

    ~ICommand() override = default;
};

}

}  // namespace game_manager
