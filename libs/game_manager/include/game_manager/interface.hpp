#pragma once

#include <filesystem>


namespace event_controller {

class IController;

}

namespace game_manager {

class IState {
  public:
    virtual void stop(event_controller::IController &controller) = 0;

    virtual void resume(event_controller::IController &controller) = 0;

    virtual ~IState() = default;
};

class Config;

class ILoaderConfig {
  protected:
    virtual void load(const std::filesystem::path &root,
                      Config &config) const = 0;

    virtual ~ILoaderConfig() = default;

    friend class Config;
};

class IInitDependencies {
  protected:
    virtual void init(Config &config) const = 0;

    virtual ~IInitDependencies() = default;

    friend class Config;
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
