#pragma once
#include <filesystem>

namespace event_controller {

class IController;

}

namespace game_manager {

class IState {
  public:
    virtual void stop(event_controller::IController &controller) const = 0;

    virtual void contine(event_controller::IController &controller) const = 0;

    virtual ~IState() = default;
};

class Config;

class ILoaderConfig {
  protected:
    virtual void load(const std::filesystem::path& root
                      , Config &config) const = 0;

    virtual ~ILoaderConfig() = default;

    friend class Config;
};

class IInitImportImplForConfig {
  protected:
    virtual void init(Config &config) const = 0;

    virtual ~IInitImportImplForConfig() = default;

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
